/// @file main.cpp
/// Definition of main function. The defined main function is for 
/// currency & distance conversions.
///
/// @author Nisha Jagtap <jagtapnisha2001@gmail.com>
///
/// (C)2024 Zeus Numerix Pvt. Ltd. All rights reserved.
/// http://www.zeusnumerix.com/

#include "jsoncons/json.hpp"
#include <iostream>
#include <string>
#include <map>
#include <fstream>

using jsoncons::json;

class Convertor {
public:
    double mFactor = 0;        ///< the conversion factor
    std::string mFromName;      ///< from unit name
    std::string mToName;        ///< to unit name
    /// convertor database file path
    const std::string afilePath  = "D:/msys2_mar24_qt6/home/Nisha Jagtap/root/"
                                    "ccpp_projects/training_projects/"
                                    "combine_converter/convertdb.json";
    
    /// constructor
    Convertor( std::string aFrom, std::string aTo, double  aFactor ) {
        mFromName = aFrom;
        mToName = aTo;
        mFactor = aFactor;
    }

    /// Get the from unit name
    std::string fromName() const { return mFromName; }
    
    /// Get the to unit name
    std::string toName() const { return mToName; }

    /// does the conversion
    double convert( double aValue ) {
        return aValue * mFactor;
    }

    /// Loads the convertor database and Prints the available conversion
    /// options menu and queries the user for a selection.
    ///
    /// @param[in] aList
    ///     List of Convertor objects.
    /// @param[in] yourChoice
    ///     User choice
    ///
    /// @return
    ///     The index of the selected option is returned. In case of an invalid
    ///     choice, -1 is returned.
    int getOption( std::map<std::string, Convertor>& aList, int yourChoice = 0 )
    {
        std::ifstream inputfile( afilePath );
        std::string type;

        /// Check if the file is opened successfully
        if (!inputfile.is_open()) {
            std::cout << "Failed to open the JSON file." << std::endl;
            return false;
        }

        /// Declare a JSON object
        json j = json::object();

        /// Parse the JSON content
        j = json::parse(inputfile);

        if ( 1 == yourChoice ) {
            std::cout << "You have selected currency conversion."<< std::endl;
            type = "currency";
        } else if ( 2 == yourChoice ) {
            std::cout << "You have selected distance conversion."<< std::endl;
            type = "distance";
        } else  if (3 == yourChoice || yourChoice > 3 || yourChoice < 1){
            std::cout << "Invalid Input" << std::endl;
            return EXIT_SUCCESS;
        }
        
        /// Iterate over the JSON array and fill the list with  
        /// Convertor objects
        for (const auto& item : j[type].array_range()) {
            std::string from = item["from"].as<std::string>();
            std::string to = item["to"].as<std::string>();
            double factor = item["factor"].as<double>();
            aList.insert(std::make_pair(from + "_" + to, 
                            Convertor(from, to, factor)));
        }

        inputfile.close();
        int index = 0;
        int choice = -1;
    
        std::cout << "Choose from below options to convert:" << std::endl;

        for ( auto& pair : aList ) {
            std::cout << "[ " << index++ + 1 << " ] " << pair.second.fromName() 
                        << " to "<< pair.second.toName() << std:: endl;
        }

        double aValue = 0;
        std::cout << "Enter your choice:";  
        std::cin >> choice;
        choice--;

        if (( 0 > choice ) || ( aList.size() <= choice )) {
            std::cout << "Invalid selection." << std::endl;
            return -1;
        } else if ( -1 < choice ) {
            std::cout << "Enter value to converts:" << std::endl;
            std::cin >> aValue;
            auto it = aList.begin();
            // Move iterator to the chosen index
            std::advance(it, choice); 
            auto result = it->second.convert(aValue);
            std::cout << "Converted value: " << result << std::endl;
        }

        return 0;
    }

};


int main() {
    // Declare an object of Convertor class
    Convertor converter( "from_unit", "to_unit", 1.0 ); 
    
    std::map<std::string, Convertor> aList{}; 

    int yourChoice = 0;

    std::cout << "Welcome to DISTANCE AND CURRENCY converter" << std::endl;
    /// Choose one from below options
    std::cout << "What you want to convert?" << std::endl;     
    /// Choose 1,if you want to make currency conversion
    std::cout << "[ 1 ] Currency Conversion" << std::endl;     
    /// Choose 2,if you want to make currency conversion
    std::cout << "[ 2 ] Distance Conversion" << std::endl;    
    /// To make conversions please give valid inputs
    std::cout << "Enter your choice:";     
    std::cin >> yourChoice;

    int choice = 0;
    choice = converter.getOption( aList, yourChoice );


    return EXIT_SUCCESS;
}




