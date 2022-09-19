#include <iostream>
#include <vector>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

#include "FlipJpegRequestHandler.h"

void FlipJpegRequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request,
	Poco::Net::HTTPServerResponse& response)
{
	std::cout << "Received a new flip jpeg request." << std::endl;

	response.setChunkedTransferEncoding(true);

	std::istream& requestStream = request.stream();

	try
	{
		std::cout << "Reading data from request stream...";
		std::vector<uint8_t> imgData{ std::istreambuf_iterator<char>(requestStream),
			std::istreambuf_iterator<char>() };
		std::cout << "Finished." << std::endl;

		cv::Mat imgMatrix = cv::imdecode(imgData, cv::IMWRITE_JPEG_QUALITY);
		imgData.clear();
		cv::flip(imgMatrix, imgMatrix, 1);   // Flip horizontally
		cv::imencode(".jpg", imgMatrix, imgData);

		std::cout << "Writing data to response stream...";
		std::ostream& responseStream = response.send();
		response.setContentType("image/jpeg");
		responseStream.write(reinterpret_cast<const char*>(&imgData[0]),
			imgData.size() * sizeof(imgData[0]));
		std::cout << "Finished." << std::endl;

		std::cout << "A responce containing flipped image has been sent."
			<< std::endl << std::endl;
	}
	catch (...)
	{
		std::cout << "Received invalid data." << std::endl << std::endl;

		response.setStatus("415");
		response.setReason("Invalid Input Data");
		response.send();

		return;
	}
}