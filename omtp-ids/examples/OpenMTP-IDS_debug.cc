// $Id$

#include <config.h>

// SYSTEM INCLUDES
//
#include <iostream>

#include <libgen.h>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//
#include <omtp-ids/OpenMTP-IDS.hh>

// FORWARD REFERENCES
//

// *********************************************************************
//
// NAME:
//   test_OpenMTP-IDS - OpenMTP-IDS test programme
//
// TYPE:          C++-PROGRAMME
// SYNOPSIS:
// DESCRIPTION:
// EXAMPLES:
// FILES:         test_OpenMTP-IDS.cc
// SEE ALSO:      OpenMTP-IDS.hh, OpenMTP-IDS.cc
//
// AUTHOR:        Deneys Maartens
// VERSION:       $Rev$
// DATE:          $Date: 2004/07/16 11:05:26 $
// COPYRIGHT:     Deneys Maartens (C) 2004
//
// LICENCE:
//   This program is free software; you can redistribute it and/or
//   modify it under the terms of the GNU General Public License as
//   published by the Free Software Foundation; either version 2, or (at
//   your option) any later version.
//
//   This program is distributed in the hope that it will be useful, but
//   WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//   General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//   02111-1307, USA.
//
// *********************************************************************

// EXTERNAL REFERENCES
//

int
main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cout << "Usage : "
			<< basename(argv[0])
			<< " OpenMTP_filename\n";

		return EXIT_FAILURE;
	}

	if (!strcmp(argv[1], "-V")) {
		std::cout << argv[0] << " " << PACKAGE_STRING << std::endl;
		return 0;
	}

	try {
		OpenMTP_IDS openmtp(argv[1]);
		openmtp.debug(std::cout);
	} catch (const char* err) {
		std::cout << basename(argv[0]) << ": "
			<< err << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

