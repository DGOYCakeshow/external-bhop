#include "memory.h"
#include "thread"

namespace offsets
{
	constexpr ::std::ptrdiff_t dwLocalPlayer = 0xDEA964;
	constexpr ::std::ptrdiff_t m_fFlags = 0x104;
	constexpr ::std::ptrdiff_t dwForceJump = 0x52BBC7C;
}


int main()
{
	const auto mem = Memory("csgo.exe");

	std::cout << "csgo found!" << std::endl;

	const auto client = mem.GetModuleAddress("client.dll");
	std::cout << "client.dll -> " << "0x" << std::hex << client << std::dec << std::endl;

	while (true)
	{
		const auto localPlayer = mem.Read<uintptr_t>(client + offsets::dwLocalPlayer);

		if (localPlayer)
		{
			const auto onGround = mem.Read<bool>(localPlayer + offsets::m_fFlags);

			if (GetAsyncKeyState(VK_SPACE) && onGround & (1 << 0))
				mem.Write<BYTE>(client + offsets::dwForceJump, 6);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

}