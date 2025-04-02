#include "OllamaService.h"
#include <array>
#include <cstdio>
#include <sstream>

namespace ai::agent::v2::ollama {

std::string execCommand(const std::string &cmd, int &exitCode) {
    std::array<char, 128> buffer;
    std::stringstream result;
    FILE* pipe = popen((cmd + " 2>&1").c_str(), "r");
    if (!pipe) {
        exitCode = -1;
        return "Failed to open pipe";
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result << buffer.data();
    }

    exitCode = pclose(pipe);
    return result.str();
}

Json::Value runModel(const std::string &model) {
    int exitCode;
    std::string command = "ollama run " + model;
    std::string output = execCommand(command, exitCode);

    Json::Value result;
    result["command"] = command;
    result["output"] = output;

    if (exitCode != 0 || output.find("could not connect to ollama app") != std::string::npos) {
        result["success"] = false;
        result["error"] = "Ollama is not running or the model failed to execute.";
    } else {
        result["success"] = true;
    }

    return result;
}

Json::Value listModels() {
    int exitCode;
    std::string command = "ollama list";
    std::string output = execCommand(command, exitCode);

    Json::Value result;
    result["command"] = command;
    result["output"] = output;

    if (exitCode != 0 || output.find("could not connect to ollama app") != std::string::npos) {
        result["success"] = false;
        result["error"] = "Ollama is not running or failed to list models.";
    } else {
        result["success"] = true;
    }

    return result;
}

}  // namespace ai::agent::v2::ollama
