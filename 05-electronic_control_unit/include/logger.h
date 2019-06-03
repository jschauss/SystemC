/*
 * logger.h
 *
 *  Created on: Sep 13, 2018
 *      Author: j_schauss18
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <fstream>

class logger
{
public:

	logger()
	{
		log.open("log.txt");
	}

	void log_to_file(std::stringstream& ss)
	{
		log << ss.str();
	}

	~logger()
	{
		log.close();
	}

private:

	std::ofstream log;

};


#endif /* LOGGER_H_ */
