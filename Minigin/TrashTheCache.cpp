#include "TrashTheCache.h"
#include <iostream>

void ttc::TrashTheCache::RunIntegerBenchmark()
{
    auto start = std::chrono::high_resolution_clock::now();

    
    std::vector<int> buffer(m_BufferSize, 1); // Initialize buffer with 1s

    for (size_t step = 1; step <= 1024; step *= 2)
    {
        

        for (size_t i = 0; i < m_BufferSize; i += step)
        {
            buffer[i] *= 2;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "operation took " << elapsedTime / 1000.f << "ms" << std::endl;
    }

    std::cout << std::endl;
}

void ttc::TrashTheCache::RunGameObjectBenchmark()
{
    std::vector<GameObject> buffer(m_BufferSize);

	for (size_t step = 1; step <= 1024; step *= 2)
	{
		auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < m_BufferSize; i += step)
		{
            buffer[i].id *= 2;
		}

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "operation took " << elapsedTime / 1000.f << "ms" << std::endl;
	}

	std::cout << std::endl;

}

void ttc::TrashTheCache::RunGameObjectAltBenchmark()
{
    std::vector<GameObjectAlt> buffer(m_BufferSize);

    for (size_t step = 1; step <= 1024; step *= 2)
    {
        auto start = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < m_BufferSize; i += step)
        {
            buffer[i].id *= 2;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "operation took " << elapsedTime / 1000.f << "ms" << std::endl;
    }

    std::cout << std::endl;
}
