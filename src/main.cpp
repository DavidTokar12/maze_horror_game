#include <boost/program_options.hpp>
#include <iostream>
#include "view/GameView.hpp"

namespace po = boost::program_options;

int main(int argc, char *argv[])
{
    po::options_description desc("Usage:");

    desc.add_options()("help", "produce help message")("play", po::value<int>(), "number of enemies")("replay", po::value<std::string>(), "file to replay");

    po::variables_map vm;
    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    }
    catch (const po::error &e)
    {
        std::cerr << "Error parsing command-line arguments: " << e.what() << "\n";
        std::cerr << desc << "\n";
        return 1;
    }

    if (vm.count("help") + vm.count("play") + vm.count("replay") > 1)
    {
        std::cerr << "Error: Only one option can be specified at a time.\n";
        std::cerr << desc << "\n";
        return 1;
    }

    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return 0;
    }

    if (vm.count("play"))
    {
        GameView gv;

        if (!gv.initialized())
        {
            std::cerr << "Game view not initialized. Exiting\n";
            return 1;
        }

        return gv.mainGameLoop();
    }

    if (vm.count("replay"))
    {
        std::cout << "Replaying file " << vm["replay"].as<std::string>() << "\n";
        return 0;
    }

    std::cerr << "Please specify a valid option!\n";
    std::cerr << desc << std::endl;
    return 1;
}