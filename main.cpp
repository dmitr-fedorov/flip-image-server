#include <iostream>
#include <vector>

#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

class FlipJpegRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
	void handleRequest(Poco::Net::HTTPServerRequest& request,
		               Poco::Net::HTTPServerResponse& response) override
	{
		response.setChunkedTransferEncoding(true);
		response.setContentType("image/jpeg");

		std::istream& requestStream = request.stream();
		std::ostream& responseStream = response.send();
		
		std::vector<uint8_t> imgData;
		std::for_each(std::istreambuf_iterator<char>(requestStream),
			          std::istreambuf_iterator<char>(),
			          [&imgData](const char& byte) { imgData.push_back(byte); }
		             );

		cv::Mat imgMatrix = cv::imdecode(imgData, cv::IMWRITE_JPEG_QUALITY);

		imgData.clear();
		cv::flip(imgMatrix, imgMatrix, 1);
		cv::imencode(".jpg", imgMatrix, imgData);
		
		for (const uint8_t& byte : imgData)
		{
			responseStream << byte;
		};
	};
};

class HandlerFactory : public Poco::Net::HTTPRequestHandlerFactory
{
public:
	Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override
	{
		return new FlipJpegRequestHandler();
	}
};

class HttpServerApplication : public Poco::Util::ServerApplication
{
protected:
	int main(const std::vector<std::string>& args) override
	{
		Poco::UInt16 port = 5875;
		Poco::Net::ServerSocket socket(port);
		Poco::Net::HTTPServerParams* pParams = new Poco::Net::HTTPServerParams();
		Poco::Net::HTTPServer server(new HandlerFactory(), socket, pParams);

		server.start();
		std::cout << "Server is running" << std::endl;
		waitForTerminationRequest();
		server.stop();

		return EXIT_OK;
	}
};

int main(int argc, char** argv)
{
	HttpServerApplication app;

	return app.run(argc, argv);
}