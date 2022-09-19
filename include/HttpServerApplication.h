#pragma once

#include <Poco/Util/ServerApplication.h>

class HttpServerApplication : public Poco::Util::ServerApplication
{
protected:
	int main(const std::vector<std::string>& args) override;
};