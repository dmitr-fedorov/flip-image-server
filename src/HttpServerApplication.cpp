#include <iostream>

#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>

#include "HttpServerApplication.h"
#include "HandlerFactory.h"

int HttpServerApplication::main(const std::vector<std::string>& args)
{
	Poco::UInt16 port = 5875;
	Poco::Net::ServerSocket socket(port);
	Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams();
	Poco::Net::HTTPServer server(new HandlerFactory(), socket, pParams);

	server.start();
	std::cout << "Server is running." << std::endl << std::endl;
	waitForTerminationRequest();
	server.stop();
	std::cout << "Server shut down." << std::endl << std::endl;

	return EXIT_OK;
}