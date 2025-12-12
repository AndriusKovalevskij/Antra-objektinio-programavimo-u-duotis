#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "student.h"
#include "operations.h"
#include "zmogus.h"
#include <vector>
#include <sstream>

// ==================================================
// TEST SUITE 1: Studentas Class Basic Functionality
// ==================================================

TEST_CASE("Studento default konstruktorius", "[studentas][constructor]")
{
    Studentas s;

    REQUIRE(s.vardas() == "");
    REQUIRE(s.pavarde() == "");
    REQUIRE(s.egzRezultatas() == 0);
    REQUIRE(s.galutinisVidurkis() == 0.0);
    REQUIRE(s.galutineMediana() == 0.0);
    REQUIRE(s.ndPazymiai().empty());
}

TEST_CASE("Studento konstruktoriai su parametrais", "[studentas][constructor]")
{
    Studentas s("Jonas", "Jonaitis");

    REQUIRE(s.vardas() == "Jonas");
    REQUIRE(s.pavarde() == "Jonaitis");
    REQUIRE(s.egzRezultatas() == 0);
    REQUIRE(s.ndPazymiai().empty());
}

TEST_CASE("Studento seteriai veikia teisingai", "[studentas][setters]")
{
    Studentas s;

    s.setVardas("Petras");
    s.setPavarde("Petraitis");
    s.setEgzRezultatas(8);

    REQUIRE(s.vardas() == "Petras");
    REQUIRE(s.pavarde() == "Petraitis");
    REQUIRE(s.egzRezultatas() == 8);
}

TEST_CASE("Studento copy konstruktorius", "[studentas][constructor]")
{
    Studentas s1("Jonas", "Jonaitis");
    s1.setEgzRezultatas(9);
    s1.addNdPazymys(8);
    s1.addNdPazymys(7);
    s1.skaiciuotiGalutini();

    Studentas s2(s1);

    REQUIRE(s2.vardas() == "Jonas");
    REQUIRE(s2.pavarde() == "Jonaitis");
    REQUIRE(s2.egzRezultatas() == 9);
    REQUIRE(s2.ndPazymiai().size() == 2);
    REQUIRE(s2.galutinisVidurkis() == s1.galutinisVidurkis());
}

TEST_CASE("Studento priskirimo operatorius", "[studentas][operators]")
{
    Studentas s1("Jonas", "Jonaitis");
    s1.setEgzRezultatas(10);
    s1.addNdPazymys(9);

    Studentas s2;
    s2 = s1;

    REQUIRE(s2.vardas() == "Jonas");
    REQUIRE(s2.pavarde() == "Jonaitis");
    REQUIRE(s2.egzRezultatas() == 10);
    REQUIRE(s2.ndPazymiai().size() == 1);
}
