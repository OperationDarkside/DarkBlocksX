#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#pragma once
//Noise
#include "noise/src/noise.h"
#include "noise/src/noiseutils.h"

namespace Blocky {

	template<unsigned N>
	class MapCreator {
	public:
		MapCreator();
		~MapCreator();

		void CreateLandscape(unsigned blocks[N][N][N]);
	};


	template<unsigned N>
	inline MapCreator<N>::MapCreator() {}

	template<unsigned N>
	inline MapCreator<N>::~MapCreator() {}

	template<unsigned N>
	inline void MapCreator<N>::CreateLandscape(unsigned blocks[N][N][N]) {
		noise::module::Perlin myModule;
		noise::utils::NoiseMap heightMap;
		noise::utils::NoiseMapBuilderPlane heightMapBuilder;

		heightMapBuilder.SetSourceModule(myModule);
		heightMapBuilder.SetDestNoiseMap(heightMap);
		heightMapBuilder.SetDestSize(N, N);
		heightMapBuilder.SetBounds(2.0, 6.0, 1.0, 5.0);
		heightMapBuilder.Build();

		for(int x = 0; x < N; ++x) {
			for(int z = 0; z < N; ++z) {
				// Use the noise library to get the height value of x, z
				//float height = m_pChunkManager->GetNoiseValue(x, z);

				// Use the height map texture to get the height value of x, z
				float height = (heightMap.GetValue(x, z) * (N - 1) * 1.0f) * 1.0f;

				for(int y = 0; y < N; y++) {
					//blocks[x][y][z].SetActive(true);
					if(y < height) {
						blocks[x][y][z] = 1;
					} else {
						blocks[x][y][z] = 0;
					}
				}
			}
		}
	}
}
#endif // !MAPCREATOR_H