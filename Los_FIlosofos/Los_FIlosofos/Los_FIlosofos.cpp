// Los_FIlosofos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <iostream>
using namespace std;

HANDLE Filosofos[5];
HANDLE mutex;
bool Tenedor[5];

DWORD WINAPI Comer(PVOID PParam) {
	std::cout << "El filosofo " << *((int*)PParam) + 1 << " esta comiendo" << endl;
	return 0;
}

DWORD WINAPI Pensar(PVOID PParam) {
	std::cout << "El filosofo " << *((int*)PParam) + 1 << " esta pensando" << endl;
	return 0;
}

DWORD WINAPI tomaTenedor(PVOID PParam) {
	DWORD id2;
	while(true)
	{
		WaitForSingleObject(mutex, INFINITE);
	if (Tenedor[*((int*)PParam)]){
		Tenedor[*((int*)PParam)] = !Tenedor[*((int*)PParam)];
		std::cout << "El filosofo " << *((int*)PParam) + 1 << " tomo el tenedor " << *((int*)PParam) + 1 << endl;
		if (4 == *((int*)PParam)){
			if (Tenedor[0])
			{
				Tenedor[0] = !Tenedor[0];
				std::cout << "El filosofo " << *((int*)PParam) + 1 << " tomo el tenedor 1" << endl;
				HANDLE FilosofoComiendo = CreateThread(nullptr, 0, Comer, nullptr, 0, &id2);
				WaitForSingleObject(FilosofoComiendo, INFINITE);
				std::cout << "El filosofo " << *((int*)PParam) + 1 << " solto el tenedor 1" << endl;
				Tenedor[0] = !Tenedor[0];
			}
		}
		else if (Tenedor[*((int*)PParam) +1])
		{
			Tenedor[*((int*)PParam) + 1] = !Tenedor[*((int*)PParam) + 1];
			std::cout << "El filosofo " << *((int*)PParam) + 1 << " tomo el tenedor " << *((int*)PParam) + 1 << endl;
			HANDLE FilosofoComiendo = CreateThread(nullptr, 0, Comer, nullptr, 0, &id2);
			WaitForSingleObject(FilosofoComiendo, INFINITE);
			std::cout << "El filosofo " << *((int*)PParam) + 1 << " solto el tenedor " << *(int*)PParam + 1 << endl;
			Tenedor[*((int*)PParam) + 1] = !Tenedor[*((int*)PParam) + 1];
		}
		std::cout << "El filosofo " << *(int*)PParam + 1 << " solto el tenedor " << *(int*)PParam + 1 << endl;
		Tenedor[*(int*)PParam] = !Tenedor[*(int*)PParam];
	}
	HANDLE FilosofoPensando = CreateThread(nullptr, 0, Pensar, nullptr, 0, &id2);
	WaitForSingleObject(FilosofoPensando, INFINITE);
		ReleaseMutex(mutex);
	}
	return 0;
}

int main()
{
	mutex = CreateMutex(nullptr, false, L"");
	DWORD idThread1;
	for (int i = 0; i < 5; i++)
	{
		Tenedor[i] = false;
	}
	for (int i = 0; i < 5; i++)
	{
		Filosofos[i] = CreateThread(nullptr, 0, tomaTenedor, nullptr, 0, &idThread1);
	}
	ReleaseMutex(mutex);
	while (true)
	{
	}
    return 0;
}

