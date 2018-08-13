

#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>

#include "json.h"

#define RAPIDJSON_SSE42

#include "include/rapidjson/document.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/writer.h"
// Short alias for this namespace
namespace pt = boost::property_tree;
using namespace rapidjson;

std::string input_string = R"(
{
    "FlightRule": "IFR",
    "WindsAloftData": false,
    "AircraftDefinition": {
    "AircraftTailNumber": "NAFIS",
    "AircraftIcaoId": "asf",
    "AircraftType": "G-V",
    "Series": "GDC",
    "EngineType": "BR710A1-",
    "Callsign": "gdc123",
    "MaxFlightLevel": 510,
    "Weights": {
    "Units": "LBS",
    "BasicMass": 45000,
    "MaxTakeOffMass": 90500,
    "MaxRampMass": 90900,
    "MaxZeroFuelMass": 54500,
    "MaxLandingMass": 75300
    },
    "Fuel": {
    "MaximumFuelCapacity": 41300,
    "TaxiFuelType": "Hour",
    "DefaultTaxiFuel": 550
    },
    "PerformanceBasedNavigation": {
    "RNAV10": false,
    "RNAV1All": false,
    "RNAV1DMEDME": false,
    "RNAV1DMEDMEIRU": false,
    "RNAV1GNSS": false,
    "RNAV2All": false,
    "RNAV2DMEDME": false,
    "RNAV2DMEDMEIRU": false,
    "RNAV2GNSS": false,
    "RNAV5All": true,
    "RNAV5DME": false,
    "RNAV5GNSS": false,
    "RNAV5INSOrIRS": false,
    "RNAV5LoranC": false,
    "RNAV5VORDME": false,
    "RNP1All": false,
    "RNP1DME": false,
    "RNP1DMEIRU": false,
    "RNP1GNSS": false,
    "RNP4": false,
    "RNPARApproachRF": false,
    "RNPARApproachNotRF": false,
    "RNPApproach": false,
    "RNPApproachBAROVNAV": false
    },
    "EquipmentCodes": {
    "StandardEquipment": true,
    "ILS": false,
    "VOR": false,
    "VHF": false,
    "GBASLandingSystem": false,
    "LPV": false,
    "LORAN": false,
    "DME": true,
    "ACARS": {
    "FMCWPRACARS": false,
    "DFIS": false,
    "PDC": false
    },
    "ADF": false,
    "GNSS": true,
    "HFRTF": false,
    "INS": true,
    "CPDLC": {
    "ATNVDLMode2": false,
    "FANS1AHFDL": false,
    "FANS1AVDLModeA": false,
    "FANS1AVDLMode2": true,
    "FANS1ASATCOMINMARSAT": false,
    "FANS1ASATCOMMTSAT": false,
    "FANS1ASATCOMIRDIUM": false
    },
    "MLS": false,
    "RTF": {
    "RTFSATCOMINMARSAT": false,
    "RTFSATCOMMTSAT": false,
    "RTFSATCOMIRDIUM": false
    },
    "CPDLCRCP400": false,
    "CPDLCRCP240": false,
    "SATVOICERCP400": false,
    "PBN": true,
    "TACAN": false,
    "UHF": true,
    "RVSM": true,
    "MNPS": true,
    "VHF833Spacing": true,
    "Other": true,
    "NAV": "",
    "COM": "",
    "DAT": "1FANSP2PDC"
    },
    "SurveillanceCodes": {
    "ModeA": false,
    "ModeAC": false,
    "ModeS": {
    "X": false,
    "I": false,
    "P": false,
    "S": true,
    "E": false,
    "H": false,
    "L": false
    },
    "ADS": {
    "ADSB1090InOut": true,
    "ADSB1090Out": false,
    "ADSBUATInOut": true,
    "ADSBUATOut": false,
    "ADSVDLMode4Out": false,
    "ADSVDLMode4OutIn": false,
    "ADSCATN": false,
    "ADSCFANS1A": false,
    "RTCA_DO-260B": false,
    "RTCA_DO-282B": false
    },
    "Frequency": {
    "ELBA": false,
    "UHF": false,
    "VHF": true
    },
    "SELCAL": "NONE",
    "USRNAV": {
    "D": 1,
    "E": 2,
    "A": 1
    },
    "PerformanceCategory": "",
    "other": ""
    },
    "Misc": {
    "DingyCover": "Y",
    "Dinghies": 2,
    "DinghiesCapacity": 9,
    "CoverColor": "yellow",
    "SurvivalEquipment": "M",
    "Jackets": {
    "L": true,
    "F": true,
    "U": false,
    "V": false
    },
    "Item18Registration": "NAFIS",
    "Item18SURRSP180": false,
    "Item18SURRSP400": false,
    "OperatingCost": 2500,
    "FuelPricePerGal": 3.5
    },
    "DefaultCruise": "85",
    "ATCRemarks": "TEST FPL",
    "AircraftColorAndMarkings": "BLUWHT",
    "Waketurbulance": "M",
    "TypeOfFlight": "General",
    "PersonsOnBoard": 0,
    "ModeSID": "",
    "NumberOfAircraft": 1,
    "Status": {
    "ALTRV": false,
    "ATFMX": false,
    "FFR": false,
    "FLTCK": false,
    "HAZMAT": false,
    "HEAD": false,
    "HOSP": false,
    "HUM": false,
    "MARSA": false,
    "MEDEVAC": false,
    "NONRVSM": false,
    "SAR": false,
    "STATE": false
    }
    },
    "FromAirport": "KLAS",
    "ToAirport": "KMMU",
    "ScheduledDeparture": "2018-07-01 11:23:00",
    "DepartureAlternate": "",
    "DestinationAlternate1": "",
    "DestinationAlternate2": "",
    "TransitionPoint": "",
    "FuelType": {
    "Type": "Depart",
    "Value": 41000
    },
    "IncludeETP": false,
    "IncludeFIR": false,
    "IncludePSR": false,
    "IncludeTOCTOD": false,
    "Payload": 100,
    "CruiseProfile": {
    "Mode": "NamedCruise",
    "Value": "LRC"
    },
    "CaptainName": "",
    "FlightLevel": 430,
    "FlightLevelToDestinationAlternate1": 0,
    "FlightLevelToDestinationAlternate2": 0,
    "FlightLevelToDepartureAlternate": 0,
    "AdditionalFuel": 100,
    "Reserve": {
    "Type": "",
    "Fuel": 0,
    "Time": 0,
    "Contingency": ""
    },
    "HoldingFuelTime": 15,
    "DestinationAlternate1Route": "",
    "DestinationAlternate2Route": "",
    "DepartureAlternateRoute": "",
    "DestinationRoute": "KLAS TRALR9 DVC GLD PWE J64 BDF J26 JOT GIJ J554 JHW LVZ4 KMMU",
    "ISADeviation": 1,
    "WindComponent": 1,
    "WindModel": "Fixed",
    "AdditionalFlightLevelPerformance": false,
    "Bias": {
    "BiasType": "Fixed",
    "ClimbFuelBias": 0,
    "ClimbTimeBias": 0,
    "CruisePercentageBias": 1,
    "DescentFuelBias": 0,
    "DescentTimeBias": 0,
    "HoldingFuelBias": 0,
    "ClimbPercentageBias": 50,
    "DescentPercentageBias": 20,
    "HoldingPercentageBias": 2,
    "HoldingTimeBias": 0
    },
    "ClimbDescentSpecifications": {
    "ClimbScheduleProfile": "250/260/M75",
    "DescentScheduleProfile": "M75/300/290"
    },
    "ETPSpecification": {
    "ETPAirports": {
    "ETP1": "",
    "ETP2": "",
    "ETP3": "",
    "ETP4": "",
    "ETP5": "",
    "ETP6": "",
    "InitialAltitude": 0,
    "FinalAltitude": 0,
    "CruiseProfile": {
    "Mode": "MACH",
    "Value": ""
    },
    "OxygenTime": 0
    }
    },
    "ETOPSpecification": {
    "ETOPAirports": {
    "ETOP1": "KLAR",
    "ETOP2": "KCOU",
    "ETOP3": "VOHS",
    "ETOP4": "",
    "ETOP5": "",
    "ETOP6": "",
    "ETOP7": "",
    "ETOP8": "",
    "ETOP9": "",
    "ETOP10": "",
    "ETOP11": "",
    "ETOP12": ""
    },
    "Minutes": 60,
    "TAS": 120
    },
    "StepClimbs": {
    "Waypoint1": "",
    "Type1": "After",
    "Level1": 0,
    "Waypoint2": "",
    "Type2": "After",
    "Level2": 0,
    "Waypoint3": "",
    "Type3": "After",
    "Level3": 0,
    "Waypoint4": "",
    "Type4": "After",
    "Level4": 0,
    "Waypoint5": "",
    "Type5": "After",
    "Level5": 0,
    "Waypoint6": "",
    "Type6": "After",
    "Level6": 0
    }
    }
)";

static inline double curr_time() {
    struct timespec now = {};
    (void)clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec + 0.000000001 * now.tv_nsec;
}

// Main Method
int main() {

    try {
        // Getting the filename
        nlohmann::json file_val_obj, spe_input;

        // Create a root
        pt::ptree root;
        std::stringstream ss;
        double taxi_type_json_val, taxi_type;
        ss << input_string;
        pt::read_json(ss, root);

        // Iterating JSON retrievals for 1 million times
        spe_input = nlohmann::json::parse(input_string);
        double start = curr_time();
        for (int j = 0; j < 1000000; ++j) {
            if (spe_input.count("AircraftDefinition") &&
                spe_input.at("AircraftDefinition").count("Fuel") &&
                spe_input.at("AircraftDefinition")
                    .at("Fuel")
                    .count("TaxiFuelType")) {
                taxi_type_json_val = spe_input.at("AircraftDefinition")
                                         .at("Fuel")
                                         .at("MaximumFuelCapacity")
                                         .get<double>();
            }
        }
        double end = curr_time();
        std::cout << "Lohmann JSON: " << (end - start) * 1000 << " ms" << '\n';

        start = curr_time();
        for (int i = 0; i < 1000000; ++i) {
            taxi_type =
                root.get<double>("AircraftDefinition.Fuel.MaximumFuelCapacity");
        }
        end = curr_time();

        std::cout << "Boost Property Tree: " << (end - start) * 1000 << " ms"
                  << '\n';

        Document d;
        const char *c = input_string.c_str();
        d.Parse(c);

        start = curr_time();
        for (int i = 0; i < 1000000; ++i) {
            Value &s    = d["AircraftDefinition"]["Fuel"]["MaximumFuelCapacity"];
            taxi_type = s.GetInt();
        }
        end = curr_time();

        std::cout << "Rapid JSON: " << (end - start) * 1000 << " ms" << '\n';
        return 0;
    } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
        return 1;
    }
}
