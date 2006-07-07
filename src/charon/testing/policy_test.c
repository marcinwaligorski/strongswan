/**
 * @file policy_test.c
 *
 * @brief Tests for the policy_t class.
 *
 */

/*
 * Copyright (C) 2005-2006 Martin Willi
 * Copyright (C) 2005 Jan Hutter
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#include "policy_test.h"

#include <daemon.h>
#include <config/policies/policy.h>
#include <config/traffic_selector.h>
#include <utils/logger.h>
#include <encoding/payloads/ts_payload.h>


/**
 * Described in header.
 */
void test_policy(protected_tester_t *tester)
{
// 	policy_t *policy;	
// // 	traffic_selector_t *ts;
// // 	linked_list_t *ts_stored, *ts_supplied, *ts_selected, *ts_expected;
// 	proposal_t *proposal1, *proposal2, *proposal3, *proposal_sel;
// 	linked_list_t *proposals_list;
// 	iterator_t *iterator;
// 	logger_t *logger;
// 	identification_t *alice, *bob;
// 	
// 	logger = logger_manager->get_logger(logger_manager, TESTER);
// 	logger->disable_level(logger, FULL);
// 	
// 	alice = identification_create_from_string("152.96.193.131");
// 	bob = identification_create_from_string("152.96.193.130");
// 	policy = policy_create("test", alice, bob);
// 	
// 	tester->assert_true(tester, (policy != NULL), "policy construction");
// 
// 	
// 	/* 
// 	 * test proposal getting and selection 
// 	 * 
// 	 */
// 	
// 	/* esp only prop */
// 	proposal1 = proposal_create(PROTO_ESP);
// 	proposal1->add_algorithm(proposal1, ENCRYPTION_ALGORITHM, ENCR_AES_CBC, 16);
// 	
// 	/* ah only prop */
// 	proposal2 = proposal_create(PROTO_AH);
// 	proposal2->add_algorithm(proposal2, INTEGRITY_ALGORITHM, AUTH_HMAC_SHA1_96, 20);
// 	
// 	policy->add_proposal(policy, proposal1);
// 	policy->add_proposal(policy, proposal2);
// 	
// 	proposals_list = policy->get_proposals(policy);
// 	tester->assert_true(tester, (proposals_list->get_count(proposals_list) == 2), "proposal count");
// 	
// 	
// 	proposals_list = linked_list_create();
// 	proposal1 = proposal_create(1);
// 	proposal1->add_algorithm(proposal1, PROTO_ESP, ENCRYPTION_ALGORITHM, ENCR_AES_CBC, 32);
// 	proposal2 = proposal_create(2);
// 	proposal2->add_algorithm(proposal2, PROTO_ESP, ENCRYPTION_ALGORITHM, ENCR_AES_CBC, 16);
// 	proposal2->add_algorithm(proposal2, PROTO_ESP, ENCRYPTION_ALGORITHM, ENCR_3DES, 16);
// 	proposal2->add_algorithm(proposal2, PROTO_ESP, ENCRYPTION_ALGORITHM, ENCR_BLOWFISH, 0);
// 	proposal2->add_algorithm(proposal2, PROTO_AH, INTEGRITY_ALGORITHM, AUTH_HMAC_SHA1_96, 20);
// 	proposal2->add_algorithm(proposal2, PROTO_AH, INTEGRITY_ALGORITHM, AUTH_HMAC_MD5_96, 20);
// 	
// 	proposals_list->insert_last(proposals_list, proposal1);
// 	proposals_list->insert_last(proposals_list, proposal2);
// 	
// 	proposal_sel = policy->select_proposal(policy, proposals_list);
// 	tester->assert_false(tester, proposal_sel == NULL, "proposal select");
// 	/* check ESP encryption algo */
// 	iterator = proposal_sel->create_algorithm_iterator(proposal_sel, PROTO_ESP, ENCRYPTION_ALGORITHM);
// 	tester->assert_false(tester, iterator == NULL, "algorithm select ESP");
// 	while (iterator->has_next(iterator))
// 	{
// 		algorithm_t *algo;
// 		iterator->current(iterator, (void**)&algo);
// 		tester->assert_true(tester, algo->algorithm == ENCR_3DES, "ESP encryption algo");
// 		tester->assert_true(tester, algo->key_size == 16, "ESP encryption keysize");
// 	}
// 	iterator->destroy(iterator);
// 	iterator = proposal_sel->create_algorithm_iterator(proposal_sel, PROTO_AH, INTEGRITY_ALGORITHM);
// 	/* check AH integrity algo */
// 	tester->assert_false(tester, iterator == NULL, "algorithm select AH");
// 	while (iterator->has_next(iterator))
// 	{
// 		algorithm_t *algo;
// 		iterator->current(iterator, (void**)&algo);
// 		tester->assert_true(tester, algo->algorithm == AUTH_HMAC_MD5_96, "ESP encryption algo");
// 		tester->assert_true(tester, algo->key_size == 20, "ESP encryption keysize");
// 	}
// 	iterator->destroy(iterator);
// 	
// 	proposal_sel->destroy(proposal_sel);
// 
// 	/* cleanup */
// 	proposal1->destroy(proposal1);
// 	proposal1->destroy(proposal2);
// 	proposals_list->destroy(proposals_list);
// 	
// 	/* 
// 	 * test traffic selection getting and matching 
// 	 * 
// 	 */
// 	
// 	ts_stored = linked_list_create();
// 	
// 	/* allow any tcp */
// 	ts = traffic_selector_create_from_string(6, TS_IPV4_ADDR_RANGE, "0.0.0.0", 0, "255.255.255.255", 65535);
// 	ts_stored->insert_last(ts_stored, (void*)ts);
// 	/* allow udp on port 123 to ".122" */
// 	ts = traffic_selector_create_from_string(7, TS_IPV4_ADDR_RANGE, "152.96.193.122", 123, "152.96.193.122", 123);
// 	ts_stored->insert_last(ts_stored, (void*)ts);
// 	/* allow udp on ports > 2000 in subnet ... */
// 	ts = traffic_selector_create_from_string(7, TS_IPV4_ADDR_RANGE, "152.96.193.0", 2000, "152.96.193.255", 65535);
// 	ts_stored->insert_last(ts_stored, (void*)ts);
// 	
// 	
// 
// 	/* define request and result */
// 	
// 	/* udp on subnet:123, should be reduced to ".122"  */
// 	ts = traffic_selector_create_from_string(7, TS_IPV4_ADDR_RANGE, "152.96.193.0", 123, "152.96.193.255", 123);
// 	ts_supplied->insert_last(ts_supplied, (void*)ts);
// 	ts_reference[0] = traffic_selector_create_from_string(7, TS_IPV4_ADDR_RANGE, "152.96.193.122", 123, "152.96.193.122", 123);
// 	
// 	/* should be granted. */
// 	ts_request[1] = traffic_selector_create_from_string(7, TS_IPV4_ADDR_RANGE, "152.96.193.0", 2000, "152.96.193.255", 2000);
// 	ts_reference[1] = traffic_selector_create_from_string(7, TS_IPV4_ADDR_RANGE, "152.96.193.0", 2000, "152.96.193.255", 2000);
// 	
// 	/* should be reduced to port 2000 - 3000. and range ".193.*" */
// 	ts_request[2] = traffic_selector_create_from_string(7, TS_IPV4_ADDR_RANGE, "152.96.191.0", 1000, "152.96.194.255", 3000);
// 	ts_reference[2] = traffic_selector_create_from_string(7, TS_IPV4_ADDR_RANGE, "152.96.193.0", 2000, "152.96.193.255", 3000);
// 	
// 	/* icmp request, should be discarded */
// 	ts_request[3] = traffic_selector_create_from_string(1, TS_IPV4_ADDR_RANGE, "0.0.0.0", 0, "255.255.255.255", 65535);
// 	
// 	policy->add_my_traffic_selector(policy, ts_policy[0]);
// 	policy->add_my_traffic_selector(policy, ts_policy[1]);
// 	policy->add_my_traffic_selector(policy, ts_policy[2]);
// 	
// 	count = policy->get_my_traffic_selectors(policy, &ts_result);
// 	tester->assert_true(tester, (count == 3), "ts get count");
// 	ts_result[0]->destroy(ts_result[0]);
// 	ts_result[0]->destroy(ts_result[1]);
// 	ts_result[0]->destroy(ts_result[2]);
// 	free(ts_result);
// 	
// 	count = policy->select_my_traffic_selectors(policy, &ts_request[0], 4, &ts_result);
// 	tester->assert_true(tester, (count == 3), "ts select count");
// 	
// 	
// 	/* store and restore into ts payload, tricky tricky */
// 	ts_payload = ts_payload_create_from_traffic_selectors(TRUE, ts_result, count);
// 	
// 	/* destroy */
// 	ts_result[0]->destroy(ts_result[0]);
// 	ts_result[0]->destroy(ts_result[1]); 
// 	ts_result[0]->destroy(ts_result[2]);
// 	free(ts_result);
// 	
// 	/* get them again out of the payload */
// 	count = ts_payload->get_traffic_selectors(ts_payload, &ts_result);
// 	ts_payload->destroy(ts_payload);
// 	
// 	
// 	
// 	int i;
// 	for (i = 0; i<count; i++)
// 	{
// 		chunk_t fa_res = ts_result[i]->get_from_address(ts_result[i]);
// 		chunk_t fa_ref = ts_reference[i]->get_from_address(ts_reference[i]);
// 		chunk_t ta_res = ts_result[i]->get_to_address(ts_result[i]);
// 		chunk_t ta_ref = ts_reference[i]->get_to_address(ts_reference[i]);
// 		u_int16_t fp_res = ts_result[i]->get_from_port(ts_result[i]);
// 		u_int16_t fp_ref = ts_reference[i]->get_from_port(ts_reference[i]);
// 		u_int16_t tp_res = ts_result[i]->get_to_port(ts_result[i]);
// 		u_int16_t tp_ref = ts_reference[i]->get_to_port(ts_reference[i]);
// 
// 		
// 		logger->log_chunk(logger, RAW, "from address result", fa_res);
// 		logger->log_chunk(logger, RAW, "from address reference", fa_ref);
// 		logger->log_chunk(logger, RAW, "to address result", ta_res);
// 		logger->log_chunk(logger, RAW, "to address reference", ta_ref);
// 		tester->assert_true(tester, fa_res.len == fa_ref.len, "from address len");
// 		tester->assert_false(tester, memcmp(fa_res.ptr, fa_ref.ptr,fa_res.len), "from address value");
// 		tester->assert_true(tester, ta_res.len == ta_ref.len, "to address len");
// 		tester->assert_false(tester, memcmp(ta_res.ptr, ta_ref.ptr,ta_res.len), "to address value");
// 		
// 		tester->assert_true(tester, fp_res == fp_ref, "from port");
// 		tester->assert_true(tester, tp_res == tp_ref, "to port");
// 		
// 		free(fa_res.ptr);
// 		free(fa_ref.ptr);
// 		free(ta_res.ptr);
// 		free(ta_ref.ptr);
// 	}
// 
// 
// 	/* destroy */
// 	ts_result[0]->destroy(ts_result[0]);
// 	ts_result[0]->destroy(ts_result[1]); 
// 	ts_result[0]->destroy(ts_result[2]);
// 	free(ts_result);	
// 	
// 	ts_policy[0]->destroy(ts_policy[0]);
// 	ts_policy[1]->destroy(ts_policy[1]);
// 	ts_policy[2]->destroy(ts_policy[2]);
// 	ts_request[0]->destroy(ts_request[0]);
// 	ts_reference[0]->destroy(ts_reference[0]);
// 	ts_request[1]->destroy(ts_request[1]);
// 	ts_reference[1]->destroy(ts_reference[1]);
// 	ts_request[2]->destroy(ts_request[2]);
// 	ts_reference[2]->destroy(ts_reference[2]);
// 	ts_request[3]->destroy(ts_request[3]);
/*
	policy->destroy(policy);*/
}
