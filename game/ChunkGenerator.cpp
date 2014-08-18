#include "ChunkGenerator.hpp"
#include "SimplexNoise.hpp"

#include "lumina/lumina.hpp"
#include "BlockType.hpp"
#include "Chunk.hpp"
#include "Map.hpp"
#include <random>
#include <math.h>
#include <string>


using namespace std;

// niedriger Wert für Oktave ergibt hügeligere Landschaft
// Perlin Noise mit Koeffizienten > 1 multipliziert ergibt höhere Steigung
ChunkGenerator::ChunkGenerator() {
  // Random Seed
  srand(time(0) + clock() + random()); // Zufallsgenerator initialisieren
  m_seed = rand() % 512;
}

void ChunkGenerator::chunkGeneration(Map& map, Vec3i spectatorPos) {

  // chunkPos ist Position des Chunks, in dem der Spectator steht in Chunkkoordinaten
  Vec2i chunkPos = map.getChunkPos(spectatorPos);
  string flachland = "Flachland";

  for(int x = chunkPos.x - 2; x <= chunkPos.x + 2; x++) {
    for(int z = chunkPos.y - 2; z <= chunkPos.y + 2; z++) {
      if(!map.exists({x * 16, 0, z * 16})) {
        map.addChunk({x, z});
        setBiomes(map, flachland, x, z);
      }
    }
  }
}

void ChunkGenerator::setBlockHeight(Map& map, int x, int z, int xi, int zj, int noise) {
  for(int k = 0; k < 128; k++) {
    xi = xi%16;
    zj = zj%16;
    if(xi % 16 < 0) {
      xi += 16;
    }
    if(zj % 16 < 0) {
      zj += 16;
    }

    if(k == noise) {
      map.getChunk({x, z}).setBlockType({xi, k, zj}, BlockType::Grass);  
    } else if(k <= noise && k >= noise - 3) {
      map.getChunk({x, z}).setBlockType({xi, k, zj}, BlockType::Dirt); //  Unter demao Noise-Wert gibt es nur Dirt
    } else if(k < (noise - 3) && k >= noise - 10) {
      map.getChunk({x, z}).setBlockType({xi, k, zj}, BlockType::Stone);
    } else {
      map.getChunk({x, z}).setBlockType({xi, k, zj}, BlockType::Air); //  Über dem Noise-Wert gibt es nur Aip
    }
  }
}

void ChunkGenerator::setBiomes(Map& map, string biometype, int x, int z) {

  int biomeNumber = 0;
  if (biometype == "Flachland"){
    biomeNumber = 1;
  }

  switch(biomeNumber) {

    case 1:
      for(int xi = x * 16; xi < (x * 16) + 16; xi++) {
        // Blöcke von oben nach unten (in Blockkoordinaten)
        for(int zj = z * 16; zj < (z * 16) + 16; zj++) {
          // Simplex Noise:
          // Berechne Werte im Intervall [-1,1] mit Simplex Noise
          double m_frequency = 0.01;
          double simpNoise = SimplexNoise::noise(m_frequency * xi, m_frequency * zj, m_seed);
          // Umrechnen von Intervall [-1,1] in Intervall [c,d]
          int noise = SimplexNoise::noiseInt(72, 79, simpNoise);

          setBlockHeight(map, x, z, xi, zj, noise);
        }
      }
      break;
    default:
      break;
  }
}