#include <iostream>
#include "TAPN/TAPN.hpp"
#include "boost/smart_ptr.hpp"
#include "boost/make_shared.hpp"
#include "Core/TAPNXmlParser.hpp"
#include "Core/VerificationOptions.hpp"
#include "Core/DiscretePart.hpp"
#include "Core/SymMarking.hpp"
#include "Verification/PWList.hpp"
#include "Core/Pairing.hpp"

using namespace std;
using namespace VerifyTAPN;
using namespace VerifyTAPN::TAPN;
using namespace boost;

void testInitMarkingParsing(const string& filename)
{
    TAPNXmlParser *parser = new TAPNXmlParser();

    boost::shared_ptr<TimedArcPetriNet> tapn = parser->Parse(filename);
    boost::shared_ptr<SymMarking> marking = parser->ParseMarking(filename, *tapn);

    std::cout << *tapn << "\n\n\n";

    std::cout << "Initial Marking:" << "\n";
    std::cout << "-------------------------------" << "\n";
    std::cout << "\nPlacement Vector:\n";

    int i = 0;
    for(std::vector<int>::const_iterator iter = marking->GetDiscretePart()->GetTokenPlacementVector().begin();iter != marking->GetDiscretePart()->GetTokenPlacementVector().end();++iter){
        std::cout << i << ":" << (*iter) << "\n";
        i++;
    }
    std::cout << "\n\nMapping Vector:\n";
    i = 0;
    for(std::vector<int>::const_iterator iter2 = marking->GetTokenMapping().GetMappingVector().begin();iter2 != marking->GetTokenMapping().GetMappingVector().end();++iter2){
        std::cout << i << ":" << (*iter2) << "\n";
        i++;
    }
}

void testIsEnabled(const string& filename)
{
	TAPNXmlParser *parser = new TAPNXmlParser();

	boost::shared_ptr<TimedArcPetriNet> tapn = parser->Parse(filename);
	tapn->Initialize();
	boost::shared_ptr<SymMarking> marking = parser->ParseMarking(filename, *tapn);

	for(TimedTransition::Vector::const_iterator iter = tapn->GetTransitions().begin(); iter != tapn->GetTransitions().end(); ++iter)
	{
		bool isEnabled = (*iter)->isEnabledBy(*tapn,*marking);

		std::cout << (*(*iter)) << " enabled: " << isEnabled << "\n";
	}
}

void testPairing(const string& filename)
{
	TAPNXmlParser *parser = new TAPNXmlParser();

	boost::shared_ptr<TimedArcPetriNet> tapn = parser->Parse(filename);
	tapn->Initialize();
	boost::shared_ptr<SymMarking> marking = parser->ParseMarking(filename, *tapn);


	for(TimedTransition::Vector::const_iterator iter = tapn->GetTransitions().begin(); iter != tapn->GetTransitions().end(); ++iter)
	{
		Pairing pair(*(*iter));

		std::cout << "Transition " << (*iter)->GetName() << " pairing:" << endl;

		std::cout << pair;
	}
}

int main(int argc, char* argv[]) {
	string filename = "/home/lassejac/Documents/Uni/development/DAT7/verifytapn/example-nets/pairing_test_net.xml";
	//testInitMarkingParsing(filename);

  //  testIsEnabled(filename);

	testPairing(filename);
    return 0;
}
