#include "stdafx.h"
#include "mtlLoader.h"

using namespace HARIKEN;

mtlLoader::~mtlLoader()
{
}

mtlLoader::mtlLoader(const char * path)
{

	loadmtl(path);

}

bool HARIKEN::mtlLoader::loadmtl(const char * path)
{

	std::string line;

	std::ifstream inFile(path);

	std::vector <std::string> siftedlines;

	while (std::getline(inFile, line)) {

		std::string read;

		for (size_t i = 0; i < line.size(); i++) {

			if (line[0] == '#')
				break;

			if (line[i] != ' ') {

				if(line[i] != '\t')
					read += line[i];

				//std::cout << read << std::endl;

				if(i + 1 == line.size())
					siftedlines.push_back(read);

			}

			else {
				//std::cout << read << std::endl;
				siftedlines.push_back(read);

				read = "";

			}

		}

	}

	int skip = 0;

	for (size_t i = 0; i < siftedlines.size(); i++) {
		//std::cout << siftedlines[i] << std::endl;
		if (i < skip)
			continue;

		if (siftedlines[i] == "newmtl") {

			mtlList.push_back(mtl());

		}

		if (siftedlines[i] == "Ns") {

			std::stringstream ss1(siftedlines[i + 1]);

			float Ns;

			ss1 >> Ns;

			mtlList[mtlList.size() - 1].Ns = Ns;

			skip = i + 1;

		}

		if (siftedlines[i] == "Ni") {

			std::stringstream ss1(siftedlines[i + 1]);

			float Ni;

			ss1 >> Ni;

			mtlList[mtlList.size() - 1].Ni = Ni;

			skip = i + 1;

		}

		if (siftedlines[i] == "d") {

			std::stringstream ss1(siftedlines[i + 1]);

			float d;

			ss1 >> d;

			mtlList[mtlList.size() - 1].d = d;

			skip = i + 1;

		}

		if (siftedlines[i] == "Tr") {

			std::stringstream ss1(siftedlines[i + 1]);

			float Tr;

			ss1 >> Tr;

			mtlList[mtlList.size() - 1].Tr = Tr;

			skip = i + 1;

		}

		if (siftedlines[i] == "Tf") {

			std::stringstream ss1(siftedlines[i + 1]);
			std::stringstream ss2(siftedlines[i + 2]);
			std::stringstream ss3(siftedlines[i + 3]);

			glm::vec3 Tf;

			ss1 >> Tf.x;
			ss2 >> Tf.y;
			ss3 >> Tf.z;

			mtlList[mtlList.size() - 1].Tf = Tf;

			skip = i + 1;

		}

		if (siftedlines[i] == "Ka") {

			std::stringstream ss1(siftedlines[i + 1]);
			std::stringstream ss2(siftedlines[i + 2]);
			std::stringstream ss3(siftedlines[i + 3]);

			glm::vec3 Ka;

			ss1 >> Ka.x;
			ss2 >> Ka.y;
			ss3 >> Ka.z;

			mtlList[mtlList.size() - 1].Ka = Ka;

			skip = i + 3;

		}

		if (siftedlines[i] == "Kd") {

			std::stringstream ss1(siftedlines[i + 1]);
			std::stringstream ss2(siftedlines[i + 2]);
			std::stringstream ss3(siftedlines[i + 3]);

			glm::vec3 Kd;

			ss1 >> Kd.x;
			ss2 >> Kd.y;
			ss3 >> Kd.z;

			mtlList[mtlList.size() - 1].Kd = Kd;

			skip = i + 3;

		}

		if (siftedlines[i] == "Ks") {

			std::stringstream ss1(siftedlines[i + 1]);
			std::stringstream ss2(siftedlines[i + 2]);
			std::stringstream ss3(siftedlines[i + 3]);

			glm::vec3 Ks;

			ss1 >> Ks.x;
			ss2 >> Ks.y;
			ss3 >> Ks.z;

			mtlList[mtlList.size() - 1].Ks = Ks;

			skip = i + 3;

		}
		
		if (siftedlines[i] == "Ke") {

			std::stringstream ss1(siftedlines[i + 1]);
			std::stringstream ss2(siftedlines[i + 2]);
			std::stringstream ss3(siftedlines[i + 3]);

			glm::vec3 Ke;

			ss1 >> Ke.x;
			ss2 >> Ke.y;
			ss3 >> Ke.z;

			mtlList[mtlList.size() - 1].Ke = Ke;

			skip = i + 3;

		}
		
	}

	return true;
}
