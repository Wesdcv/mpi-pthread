#!/bin/bash

#PBS -l walltime=00:01:00,nodes=1:ppn=2
#PBS -N task1
#PBS -q batch

cd $PBS_O_WORKDIR
mpirun --hostfile $PBS_NODEFILE -np 2 ./a.out 



#PBS -l walltime=00:01:00,nodes=1:ppn=5
cd $PBS_O_WORKDIR
mpirun --hostfile $PBS_NODEFILE -np 5 ./a.out 



#PBS -l walltime=00:01:00,nodes=3:ppn=5
cd $PBS_O_WORKDIR
mpirun --hostfile $PBS_NODEFILE -np 15 ./a.out 




