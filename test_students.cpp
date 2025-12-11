#include <gtest/gtest.h>
#include "student.h"
#include "zmogus.h"
#include <sstream>
#include <vector>

// ============================================================================
// TESTAI BAZINEI KLASEI ZMOGUS
// ============================================================================

TEST(ZmogusTest, DefaultKonstruktorius) {
    // Kadangi Zmogus yra abstrakti klase, testuojame per Studentas
    Studentas s;
    EXPECT_EQ(s.vardas(), "");
    EXPECT_EQ(s.pavarde(), "");
}

TEST(ZmogusTest, KonstruktoriusSuParametrais) {
    Studentas s("Jonas", "Jonaitis");
    EXPECT_EQ(s.vardas(), "Jonas");
    EXPECT_EQ(s.pavarde(), "Jonaitis");
}

TEST(ZmogusTest, SeteriaiVeikia) {
    Studentas s;
    s.setVardas("Petras");
    s.setPavarde("Petraitis");
    EXPECT_EQ(s.vardas(), "Petras");
    EXPECT_EQ(s.pavarde(), "Petraitis");
}

TEST(ZmogusTest, CopyKonstruktorius) {
    Studentas s1("Ona", "Onaite");
    Studentas s2(s1);
    EXPECT_EQ(s2.vardas(), "Ona");
    EXPECT_EQ(s2.pavarde(), "Onaite");
}

TEST(ZmogusTest, AssignmentOperatorius) {
    Studentas s1("Petras", "Petraitis");
    Studentas s2;
    s2 = s1;
    EXPECT_EQ(s2.vardas(), "Petras");
    EXPECT_EQ(s2.pavarde(), "Petraitis");
}

// ============================================================================
// TESTAI STUDENTAS KLASEI - KONSTRUKTORIAI
// ============================================================================

TEST(StudentasTest, DefaultKonstruktorius) {
    Studentas s;
    EXPECT_EQ(s.vardas(), "");
    EXPECT_EQ(s.pavarde(), "");
    EXPECT_EQ(s.egzRezultatas(), 0);
    EXPECT_TRUE(s.ndPazymiai().empty());
    EXPECT_DOUBLE_EQ(s.galutinisVidurkis(), 0.0);
    EXPECT_DOUBLE_EQ(s.galutineMediana(), 0.0);
}

TEST(StudentasTest, KonstruktoriusSuParametrais) {
    Studentas s("Ona", "Onaite");
    EXPECT_EQ(s.vardas(), "Ona");
    EXPECT_EQ(s.pavarde(), "Onaite");
    EXPECT_EQ(s.egzRezultatas(), 0);
}

TEST(StudentasTest, CopyKonstruktorius) {
    Studentas s1("Antanas", "Antanaitis");
    s1.setEgzRezultatas(8);
    s1.addNdPazymys(7);
    s1.addNdPazymys(9);
    s1.skaiciuotiGalutini();

    Studentas s2(s1);

    EXPECT_EQ(s2.vardas(), "Antanas");
    EXPECT_EQ(s2.pavarde(), "Antanaitis");
    EXPECT_EQ(s2.egzRezultatas(), 8);
    EXPECT_EQ(s2.ndPazymiai().size(), 2);
    EXPECT_DOUBLE_EQ(s2.galutinisVidurkis(), s1.galutinisVidurkis());
}

TEST(StudentasTest, AssignmentOperatorius) {
    Studentas s1("Jonas", "Jonaitis");
    s1.setEgzRezultatas(9);
    s1.addNdPazymys(8);
    s1.skaiciuotiGalutini();

    Studentas s2;
    s2 = s1;

    EXPECT_EQ(s2.vardas(), "Jonas");
    EXPECT_EQ(s2.pavarde(), "Jonaitis");
    EXPECT_EQ(s2.egzRezultatas(), 9);
    EXPECT_EQ(s2.ndPazymiai().size(), 1);
}
