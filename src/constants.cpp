/**
 * All the global constants of the game (definition)
 * @file constants.hpp
 * @author Maxence
 * @version 1.0
*/

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>


#include "Engine/json.hpp"

#include "constants.hpp"

using json = nlohmann::json;
namespace fs = std::filesystem;

Constants::Constants() {

    CWD = std::filesystem::current_path().parent_path();
    assetsPath = CWD / std::string("assets");
    configPath = assetsPath / std::string("config.json");

    SCALING_FACTOR = 1;

    WIDTH_IN_PIXELS = 600 * SCALING_FACTOR; //px
    HEIGHT_IN_PIXELS = 520 * SCALING_FACTOR; //px

    BOARD_OFFSET_X = 200 * SCALING_FACTOR; //px
    BOARD_OFFSET_Y = 10 * SCALING_FACTOR; //px

    WIDTH_IN_CELLS = 10;
    HEIGHT_IN_CELLS = 25;
    CELL_SIZE = 20 * SCALING_FACTOR; //px
    BORDER_SIZE = 0.1 * SCALING_FACTOR; //px

    DIGIT_H = 20 * SCALING_FACTOR; //px
    DIGIT_W = 10 * SCALING_FACTOR; //px
    DIGIT_X0 = 20 * SCALING_FACTOR; //px
    DIGIT_Y0 = 25 * SCALING_FACTOR; //px
    DIGIT_OFFSET = 13 * SCALING_FACTOR; //px
}

void Constants::readScalingFactor() {

    if(!std::filesystem::exists(configPath)) {
        std::cout << "Impossible to find the configuration file at" << configPath.string() << ".\n";
        throw std::runtime_error("Impossible to load data file");
    }

    // Read JSON file
    std::ifstream file(configPath);
    json data;
    file >> data;
    
    std::string strScalingFactor = data["scale"].get<std::string>();

    SCALING_FACTOR = ::atof(strScalingFactor.c_str());

}

void Constants::defineLengths() {

    WIDTH_IN_PIXELS = 600 * SCALING_FACTOR; //px
    HEIGHT_IN_PIXELS = 520 * SCALING_FACTOR; //px

    BOARD_OFFSET_X = 200 * SCALING_FACTOR; //px
    BOARD_OFFSET_Y = 10 * SCALING_FACTOR; //px

    WIDTH_IN_CELLS = 10;
    HEIGHT_IN_CELLS = 25;
    CELL_SIZE = 20 * SCALING_FACTOR; //px
    BORDER_SIZE = 0.1 * SCALING_FACTOR; //px

    DIGIT_H = 20 * SCALING_FACTOR; //px
    DIGIT_W = 10 * SCALING_FACTOR; //px
    DIGIT_X0 = 20 * SCALING_FACTOR; //px
    DIGIT_Y0 = 25 * SCALING_FACTOR; //px
    DIGIT_OFFSET = 13 * SCALING_FACTOR; //px

}

void Constants::setup() {
    
    readScalingFactor();

    defineLengths();

}