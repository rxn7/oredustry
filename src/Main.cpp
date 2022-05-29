#include "Oredustry.h"

int main(int argc, const char **argv) {
	std::unique_ptr<Oredustry> oredustry = std::make_unique<Oredustry>();
	oredustry->Start();

	return 0;
}
