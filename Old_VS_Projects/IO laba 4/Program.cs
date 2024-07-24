using System;
using System.Collections.Generic;
using System.Linq;
using CData;
using CIOhelper;
using CTransportTask;

namespace IO_laba_2
{
    class Program
    {
        static void Main(string[] args)
        {
            string Task0 = @" 
                Reserves: 20, 40 ;
                Needs: 10, 20, 30 ;
                Costs(a/b):
                2, 3, 4, 
                1, 2, 5
    
                end
            ";  // задача с соблюдением баланса

            string Task1 = @"
                Reserves: 20, 40 ;
                Needs: 30, 30, 20 ;
                Costs(a/b):
                1, 2, 3, 
                2, 3, 3
    
                end
            ";  // задача без соблюдения баланса

            Data PotentialTask0 = new Data();
          /*Reserves: 20, 40;
            Needs: 10, 20, 30;
            Costs(a / b):
            2[10], 3[10], 4[], 
            1[],   2[10], 5[30]

            end*/
            PotentialTask0.Costs = new List<List<int>>
            {
                new List<int> { 2, 3, 4 },
                new List<int> { 1, 2, 5 },
            };
            PotentialTask0.Reserves = new List<int> { 20, 20 };
            PotentialTask0.Needs = new List<int> { 10, 20, 30 };
            PotentialTask0.NumberOfProviders = 2;
            PotentialTask0.NumberOfClients = 3;
            PotentialTask0.Routes = new List<List<int>>
            {
                new List<int> { 10, 10, 0 },
                new List<int> { 0, 10, 30 },
            };
            PotentialTask0.InvolvedRoutes = new HashSet<(int, int)>
            {
                (0, 0),
                (0, 1),
                (1, 1),
                (1, 2)
            };

            Data PotentialTask1 = new Data();
            /*Reserves: 20, 40, 20;
              Needs: 30, 30, 20;
              Costs(a / b):
              1[10], 2[10], 3[], 
              2[],   3[20], 3[20]
              0[20], 0[],   0[]

              end*/
            PotentialTask1.Costs = new List<List<int>>
            {
                new List<int> { 1, 2, 3 },
                new List<int> { 2, 3, 3 },
                new List<int> { 0, 0, 0 },
            };
            PotentialTask1.Reserves = new List<int> { 20, 40, 20 };
            PotentialTask1.Needs = new List<int> { 30, 30, 20 };
            PotentialTask1.NumberOfProviders = 3;
            PotentialTask1.NumberOfClients = 3;
            PotentialTask1.Routes = new List<List<int>>
            {
                new List<int> { 10, 10, 0 },
                new List<int> { 0, 20, 20 },
                new List<int> { 20, 0, 0 },
            };
            PotentialTask1.InvolvedRoutes = new HashSet<(int, int)>
            {
                (0, 0),
                (0, 1),
                (1, 1),
                (1, 2),
                (2, 0)
            };

            TransportTask.PotentialMethod(TransportTask.MinElementMethod(IOhelper.Parse(Task1)));
            //TransportTask.PotentialMethod(PotentialTask1);
        }
    }
}
