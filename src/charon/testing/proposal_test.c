/**
 * @file proposal_test.c
 *
 * @brief Tests for the proposal_t class.
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

#include "proposal_test.h"

#include <daemon.h>
#include <config/proposal.h>
#include <utils/logger.h>


/**
 * Described in header.
 */
void test_proposal(protected_tester_t *tester)
{
	proposal_t *proposal1, *proposal2, *proposal3, *proposal4;
	iterator_t *iterator;
	algorithm_t *algo;
	bool result;

	proposal1 = proposal_create(PROTO_ESP);
	proposal1->add_algorithm(proposal1, ENCRYPTION_ALGORITHM, ENCR_3DES, 0);
	proposal1->add_algorithm(proposal1, ENCRYPTION_ALGORITHM, ENCR_AES_CBC, 256);
	proposal1->add_algorithm(proposal1, ENCRYPTION_ALGORITHM, ENCR_AES_CBC, 128);
	proposal1->add_algorithm(proposal1, ENCRYPTION_ALGORITHM, ENCR_BLOWFISH, 0);
	proposal1->add_algorithm(proposal1, INTEGRITY_ALGORITHM, AUTH_HMAC_SHA1_96, 0);
	proposal1->add_algorithm(proposal1, INTEGRITY_ALGORITHM, AUTH_HMAC_MD5_96, 0);
	proposal1->add_algorithm(proposal1, DIFFIE_HELLMAN_GROUP, MODP_1024_BIT, 0);
	proposal1->add_algorithm(proposal1, DIFFIE_HELLMAN_GROUP, MODP_2048_BIT, 0);
	
	proposal2 = proposal_create(PROTO_ESP);
	proposal2->add_algorithm(proposal2, ENCRYPTION_ALGORITHM, ENCR_3IDEA, 0);
	proposal2->add_algorithm(proposal2, ENCRYPTION_ALGORITHM, ENCR_AES_CBC, 128);
	proposal2->add_algorithm(proposal2, INTEGRITY_ALGORITHM, AUTH_HMAC_MD5_96, 0);
	proposal2->add_algorithm(proposal2, DIFFIE_HELLMAN_GROUP, MODP_1024_BIT, 0);
	
	/* ah and esp prop */
	proposal3 = proposal1->select(proposal1, proposal2);
	tester->assert_false(tester, proposal3 == NULL, "proposal select");
	if (proposal3)
	{
		result = proposal3->get_algorithm(proposal3, ENCRYPTION_ALGORITHM, &algo);
		tester->assert_true(tester, result, "encryption algo select");
		tester->assert_true(tester, algo->algorithm == ENCR_AES_CBC, "encryption algo");
		tester->assert_true(tester, algo->key_size == 128, "encryption keylen");
		
		
		result = proposal3->get_algorithm(proposal3, INTEGRITY_ALGORITHM, &algo);
		tester->assert_true(tester, result, "integrity algo select");
		tester->assert_true(tester, algo->algorithm == AUTH_HMAC_MD5_96, "integrity algo");
		
		iterator = proposal3->create_algorithm_iterator(proposal3, INTEGRITY_ALGORITHM);
		tester->assert_false(tester, iterator == NULL, "integrity algo select");
		while(iterator->has_next(iterator))
		{
			iterator->current(iterator, (void**)&algo);
			tester->assert_true(tester, algo->algorithm == AUTH_HMAC_MD5_96, "integrity algo");
		}
		iterator->destroy(iterator);
		proposal3->destroy(proposal3);
	}
	
	proposal1->destroy(proposal1);
	proposal2->destroy(proposal2);
	
	/* from string tests */
	
	proposal1 = proposal_create_from_string(PROTO_ESP, "3des-md5!");
	proposal2 = proposal_create_from_string(PROTO_ESP, "3des-md5-modp1024!");
	proposal3 = proposal_create_from_string(PROTO_ESP, "aes256-sha1");
	
	proposal4 = proposal1->select(proposal1, proposal2);
	tester->assert_true(tester, proposal4 == NULL, "from string 1");
	
	proposal4 = proposal1->select(proposal1, proposal3);
	tester->assert_true(tester, proposal4 != NULL, "from string 2");
	
	result = proposal4->get_algorithm(proposal4, ENCRYPTION_ALGORITHM, &algo);
	tester->assert_true(tester, result, "from string 3");
	tester->assert_true(tester, algo->algorithm == ENCR_3DES, "from string 4");
	result = proposal4->get_algorithm(proposal4, INTEGRITY_ALGORITHM, &algo);
	tester->assert_true(tester, result, "from string 5");
	tester->assert_true(tester, algo->algorithm == AUTH_HMAC_MD5_96, "from string 6");
	
	return;
}
