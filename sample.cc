#include <fstream>
#include <iostream>
#include <random>
#include <utility>
#include <vector>


using std::cerr;
using std::cout;
using std::endl;


[[ noreturn ]] void Usage( char const * i_argv0 );


int main( int argc, char const * argv[] ) {

	bool                     bHeader = false;
	unsigned                 argNext = 1;
	unsigned                 linesOut;
	unsigned                 linesIn = 0;
	std::random_device       rd;
	std::mt19937             mt( rd() );
	std::string              st;
	std::string              stHeader;
	std::vector<std::string> vLines;
	std::vector<unsigned>    vIn;
	std::vector<unsigned>    vOut;

	//  Parse arguments.
	if ( argc < 3 || argc > 4 )
		Usage( argv[ 0 ] );

	if ( 4 == argc ) {
		if ( 0 != strcmp( argv[ 1 ], "-h" ) )
			Usage( argv[ 0 ] );
		bHeader = true;
		argNext += 1;
	}

	std::ifstream ifsFile( argv[ argNext++ ] );
	linesOut = static_cast< unsigned >( std::stoul( argv[ argNext ] ) );
	if ( 0 == linesOut )
		Usage( argv[ 0 ] );

	//  Optionally save header.
	if ( bHeader )
		std::getline( ifsFile, stHeader );

	//  Read whole file into memory (sorry Nagesh ;-) ) and count the lines.
	while ( std::getline( ifsFile, st ) ) {
		vLines.emplace_back( std::move( st ) );
		vIn.emplace_back( linesIn++ );
	}

	//  Validate the requested number of samples.
	if ( linesOut > linesIn ) {
		cerr << "Requested " << linesOut << " samples but only "
			<< linesIn << " candidates were found." << endl;
		return 20;
	}

	//  Choose lines from the input at random (using the Knuth shuffle).
	for ( unsigned u = 0 ; u < linesOut ; u += 1 ) {
		unsigned uLine = mt() % linesIn;
		vOut.push_back( vIn[ uLine ] );
		linesIn -= 1;
		std::iter_swap( vIn.begin() + uLine, vIn.begin() + linesIn );
	}

	//  Put the selected lines back in the original order.
	std::sort( vOut.begin(), vOut.end() );

	//  Write the output (including optional header).
	if ( bHeader )
		cout << stHeader << endl;

	for ( auto it : vOut )
		cout << vLines[ it ] << endl;

	return 0;

}


[[noreturn]] void Usage( char const * i_argv0 ) {
	cerr << endl
		<< "Usage:" << endl
		<< "YourPrompt> " << i_argv0 << " [-h] <filename> <sample-size>" << endl
		<< endl;
	exit( 10 );
}
