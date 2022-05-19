#include "Oredustry.h"

int main(int argc, const char **argv) {
	std::ios::sync_with_stdio(false);
	od::Init();
	od::Start();
	od::Shutdown();
}
