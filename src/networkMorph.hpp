// An isomorphic network reproduces the sensory-motor behaviors of another network.
// A homomorphic network additionally mirrors the neuron configuration of the other network.

#ifndef __MORPHNET_HPP__
#define __MORPHNET_HPP__

#include "network.hpp"
#include "behavior.hpp"

// Mutable parameter.
class MutableParm
{
public:

   MutableParm();
   MutableParm(float minimum, float maximum, float maxDelta,
               float randomProbability);
   void init(float minimum, float maximum, float maxDelta,
             float randomProbability);

   float value;
   float minimum;
   float maximum;
   float maxDelta;
   float randomProbability;

   void initValue(Random *randomizer);
   void setValue(float value);
   void mutateValue(Random *randomizer);
   void load(FILE *fp);
   void save(FILE *fp);
   void print();
};

// Network isomorph/homomorph.
class NetworkMorph
{
public:

   // Maximum tolerated motor output error.
   static const float MAX_ERROR_TOLERANCE;

   // Constructors.
   NetworkMorph(MutableParm& excitatoryNeuronsParm, MutableParm& inhibitoryNeuronsParm,
                MutableParm& synapsePropensitiesParm, MutableParm& synapseWeightsParm,
                int numSensors, int numMotors, Random *randomizer, int tag = 0);
   NetworkMorph(MutableParm& excitatoryNeuronsParm, MutableParm& inhibitoryNeuronsParm,
                MutableParm& synapsePropensitiesParm, MutableParm& synapseWeightsParm,
                Network *homomorph, Random *randomizer, int tag = 0);
   NetworkMorph(FILE *fp, Random *randomizer);

   // Destructor.
   ~NetworkMorph();

   MutableParm excitatoryNeuronsParm;
   MutableParm inhibitoryNeuronsParm;
   MutableParm synapsePropensitiesParm;
   MutableParm synapseWeightsParm;

   Network *network;
   int     tag;
   float   error;

   // Evaluate behavior.
   void evaluate(vector<Behavior *>& behaviors, Network *homomorph = NULL);

   // Mutate.
   void mutate();

   // Clone.
   NetworkMorph *clone();

   // Load.
   void load(FILE *fp);

   // Save.
   void save(FILE *fp);

   // Print.
   void print();

private:

   Random *randomizer;

   void deleteIndexedNeuron(int index);
   void addIndexedNeuron(int index, bool excitatory);
};

// Network morphogenesis.
class NetworkMorphoGenesis
{
public:

   // Constructor.
   NetworkMorphoGenesis(vector<Behavior *>& behaviors,
                        Network *homomorph, bool homomorphClones,
                        MutableParm& excitatoryNeuronsParm, MutableParm& inhibitoryNeuronsParm,
                        MutableParm& synapsePropensitiesParm, MutableParm& synapseWeightsParm,
                        int populationSize, int numOffspring, int numGenerations,
                        RANDOM randomSeed);

   // Destructor.
   ~NetworkMorphoGenesis();

   // Behaviors.
   vector<Behavior *> behaviors;

   // Homomorphic network.
   Network *homomorph;

   // Initial population of homomorph clones?
   bool homomorphClones;

   // Evolution parameters.
   int populationSize;
   int numOffspring;

   // Network population.
   vector<NetworkMorph *> population;

   // Run parameters.
   int numGenerations;

   // Random seed.
   RANDOM randomSeed;

   // Morph networks.
   void morph();

   // Prune unfit members.
   void prune();

   // Mutate members.
   void mutate();

   // Save networks.
   void saveNetworks(char *filePrefix);

   // Print.
   void print();

private:

   Random *randomizer;
};
#endif
