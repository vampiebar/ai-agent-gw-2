#pragma once
#include <drogon/HttpController.h>

using namespace drogon;

class OllamaController : public drogon::HttpController<OllamaController> {
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(OllamaController::runModel, "/run/{1}", Get);
        ADD_METHOD_TO(OllamaController::listModels, "/list", Get);
        ADD_METHOD_TO(OllamaController::handleOperation, "/operation", Post);
    METHOD_LIST_END

    void runModel(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, std::string model);
    void listModels(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void handleOperation(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
};
