#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "p3170153-p3170031-res2.h"
#include <unistd.h>

#define BILLION  1000000000L

pthread_mutex_t countMutex;
pthread_mutex_t basicmutex;
pthread_mutex_t timemutex;
pthread_mutex_t cashierMutex;
pthread_mutex_t Zonemutex;
pthread_cond_t countCashierCondition;
pthread_cond_t countThresholdCondition;
int tilefonites = 8;
int cashier = 4;
int seed;
int card;
int bank_account;
int counter_syn;
int available_seats = 250;
int theatre_plan[25][10];
double time_wait=0;
double time_service=0;
int N=0;
int seatZoneA = 50;
int seatZoneB = 100 ;
int seatZoneC = 100;

void *pelatis(void *t) {
	struct timespec start, start2, stop, stop2;
	int *threadId = (int *)t;
	int rc;
	int seats;
	int seatsneeded;
	int pay;
	int seatSt;
	int row;
	int zoneChooser;
	int checker = 0;


	rc = pthread_mutex_lock(&countMutex);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(&rc);
	}		

	while (tilefonites == 0) {
		
		printf("----------------------------------------------------------------------\n");
		printf("O pelatis %d, den brike diathesimo tilefoniti.Blocked...\n", *threadId);	
		printf("----------------------------------------------------------------------\n");
		if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
      		perror( "clock gettime" );
      		exit( EXIT_FAILURE );
		}
		rc = pthread_cond_wait(&countThresholdCondition, &countMutex);
		
		if (rc != 0) {	
			printf("ERROR: return code from pthread_cond_wait() is %d\n", rc);
			pthread_exit(&rc);
		}
		if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      		perror( "clock gettime" );
      		exit( EXIT_FAILURE );
    	}
		time_wait += ( stop.tv_sec - start.tv_sec ) + (double)( stop.tv_nsec - start.tv_nsec ) / BILLION;

	}
    //KSEKINAEI H EKSYPHRETHSH 
    tilefonites--;
	rc = pthread_mutex_unlock(&countMutex);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(&rc);
	}	

    
    
	rc = pthread_mutex_lock(&timemutex);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(&rc);
	}

	if( clock_gettime( CLOCK_REALTIME, &start2) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }

    //ektelesh methodou
    rc = pthread_mutex_lock(&Zonemutex);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
		pthread_exit(&rc);
	}		

    seats = (rand_r(&seed) % (Nseathigh-Nseatlow + 1)) + Nseatlow;

	int srcTime =  (rand_r(&seed) % (Tseathigh-Tseatlow + 1)) + Tseatlow;
    sleep(srcTime);
    if(available_seats > 0){
			
             zoneChooser = rand_r(&seed)%100;

            if(zoneChooser <= PzoneA){
                if(seatZoneA - seats > 0){
					seatsneeded = seats;
					int i = 0;
					while(seatsneeded > 0 && i < NzoneA){
						seatsneeded = seats;
						int j = 0;
						while(j < Nseat && seatsneeded > 0){
							if(theatre_plan[i][j] == -10 ){
							if(seatsneeded == seats) {
								seatSt = j;
								row = i;
							}
							seatsneeded--;
							if (!seatsneeded){
								checker = 1;
							}
							}
							j++;
							
						}
						i++;
					}
					

				}else{
					printf("Den yparxoun arketes theseis sth zwnh A\n");
				}
			}
			else if(zoneChooser <= (PzoneA + PzoneC) && zoneChooser > PzoneA) {
				if(seatZoneB - seats > 0){
				seatsneeded = seats;
				int i = NzoneA;
				while(seatsneeded > 0 && i < NzoneA + NzoneB){
					seatsneeded = seats;
					int j = 0;
					while(j < Nseat && seatsneeded > 0){
						if(theatre_plan[i][j] == -10 ){
						if(seatsneeded == seats) {
							seatSt = j;
							row = i;
						}
						seatsneeded--;
						if (!seatsneeded){
							checker = 1;
						}
						}
						j++;
						
					}
					i++;
				}
				

				}else{
					printf("Den yparxoun arketes theseis sth zwnh B\n");
				}

			} else{
				if(seatZoneC - seats > 0){
					seatsneeded = seats;
					int i = NzoneA + NzoneB;
					while(seatsneeded > 0 && i < NzoneA + NzoneB + NzoneC){
						seatsneeded = seats;
						int j = 0;
						while(j < Nseat && seatsneeded > 0){
							if(theatre_plan[i][j] == -10 ){
							if(seatsneeded == seats) {
								seatSt = j;
								row = i;
							}
							seatsneeded--;
							if (!seatsneeded){
								checker = 1;
							}
							}
							j++;
							
						}
						i++;
					}
					

				}else{
					printf("Den yarxoun arketes thseis sth zwnh C\n");
				}


			}
            
			if(checker){
				for(int k = seatSt;k < seatSt + seats;k++){
					theatre_plan[row][k] = 0;
				}
			}

            
			
			rc = pthread_mutex_unlock(&Zonemutex);
			if (rc != 0) {	
				printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
				pthread_exit(&rc);
			}	
			

    } else {
		printf("----------------------------------------------------------------------\n");
		printf("To theatro einai gemato.\n");
		printf("----------------------------------------------------------------------\n");
	}
	tilefonites++;
	rc = pthread_cond_signal(&countThresholdCondition);
	rc = pthread_mutex_unlock(&countMutex);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(&rc);
	}
	
	//TELOS EKSYPHRETHSHS
    
    if(checker){
		//Cahier
		rc = pthread_mutex_lock(&cashierMutex);
		if (rc != 0) {	
			printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
			pthread_exit(&rc);
		}		

		while (cashier == 0) {
			
			printf("----------------------------------------------------------------------\n");
			printf("O pelatis %d, den brike diathesimo tamia.Blocked...\n", *threadId);	
			printf("----------------------------------------------------------------------\n");
			
			rc = pthread_cond_wait(&countCashierCondition, &cashierMutex);
			
			if (rc != 0) {	
				printf("ERROR: return code from pthread_cond_wait() is %d\n", rc);
				pthread_exit(&rc);
			}
			

		}
		
		cashier--;
		rc = pthread_mutex_unlock(&cashierMutex);
		if (rc != 0) {	
			printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
			pthread_exit(&rc);
		}	
		//lock mutex for the seats
				rc = pthread_mutex_lock(&basicmutex);
				if (rc != 0) {	
					printf("ERROR: return code from pthread_mutex_lock() is %d\n", rc);
					pthread_exit(&rc);
				}

				if((rand_r(&seed)%100) <= Pcardsuccess){
					counter_syn++;
					printf("----------------------------------------------------------------------\n");
					printf("H krathsh oloklhrwthike epityxws.O arithmos synallaghs einai: %d,\noi theseis sas einai: \n",counter_syn);
					for(int k = seatSt; k < (seatSt + seats); k++){
						theatre_plan[row][k]	= *threadId;
						printf("row %d and place %d \n",row + 1,k+1);
						
					}
					if(row < NzoneA){
						pay = seats*CzoneA;
						seatZoneA -= seats;
					}else if (row >= NzoneA && row < (NzoneA+ NzoneB)){
						pay = seats*CzoneB;
						seatZoneB -= seats;
					}else {
						pay = seats*CzoneC;
						seatZoneC -= seats;
					}
					printf("\nTo kostos synallaghs einai %d eyrw.\n",pay);
					bank_account += pay;
					available_seats -= seats;
					N++;
					printf("----------------------------------------------------------------------\n");
					
				}
				else{
					for(int k = seatSt;k < seatsneeded + seats;k++){
					theatre_plan[row][k] = -10;
					}
					
					printf("----------------------------------------------------------------------\n");
					printf("H krathsh mataiwthike giati h synallagh me pistwtikh karta den egine apodekth.\n");
					printf("----------------------------------------------------------------------\n");
				}
				//unlock mutex of the seats
				rc = pthread_mutex_unlock(&basicmutex);
				if (rc != 0) {	
					printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
					pthread_exit(&rc);
				}

				cashier++;
		rc = pthread_cond_signal(&countCashierCondition);
		rc = pthread_mutex_unlock(&cashierMutex);
		if (rc != 0) {	
			printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
			pthread_exit(&rc);
		}
	}

	if( clock_gettime( CLOCK_REALTIME, &stop2) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
	time_service += ( stop2.tv_sec - start2.tv_sec ) + (double)( stop2.tv_nsec - start2.tv_nsec ) / BILLION;
	rc = pthread_mutex_unlock(&timemutex);
	if (rc != 0) {	
		printf("ERROR: return code from pthread_mutex_unlock() is %d\n", rc);
		pthread_exit(&rc);
	}

	pthread_exit(t);
}

int main(int argc, char *argv[]) {

	if (argc != 3) {
		printf("ERROR: the program should take one argument, the number of threads to create!\n");
		exit(-1);
	}

	int Ncust = atoi(argv[1]);
    seed = atoi(argv[2]);
    int rc;

	
	if (Ncust < 0) {
		printf("ERROR: the number of threads to run should be a positive number. Current number given %d.\n",Ncust);
		exit(-1);
	}

	for(int k =0 ; k < NzoneA + NzoneB + NzoneC;k++){
		for(int n =0; n < Nseat; n++){
			theatre_plan[k][n] = -10;
		}
	}

    rc = pthread_mutex_init(&countMutex, NULL);
	if (rc != 0) {
    	printf("ERROR: return code from pthread_mutex_init() is %d\n", rc);
       	exit(-1);
	}

  	rc = pthread_cond_init(&countThresholdCondition, NULL);
	if (rc != 0) {
    	printf("ERROR: return code from pthread_cond_init() is %d\n", rc);
       	exit(-1);
	}

    rc = pthread_mutex_init(&basicmutex, NULL);
	if (rc != 0) {
    	printf("ERROR: return code from pthread_mutex_init() is %d\n", rc);
       	exit(-1);
	}

	rc = pthread_mutex_init(&timemutex, NULL);
	if (rc != 0) {
    	printf("ERROR: return code from pthread_mutex_init() is %d\n", rc);
       	exit(-1);
	}

	rc = pthread_mutex_init(&Zonemutex, NULL);
	if (rc != 0) {
    	printf("ERROR: return code from pthread_mutex_init() is %d\n", rc);
       	exit(-1);
	}

	rc = pthread_mutex_init(&cashierMutex, NULL);
	if (rc != 0) {
    	printf("ERROR: return code from pthread_mutex_init() is %d\n", rc);
       	exit(-1);
	}

	rc = pthread_cond_init(&countCashierCondition, NULL);
	if (rc != 0) {
    	printf("ERROR: return code from pthread_cond_init() is %d\n", rc);
       	exit(-1);
	}
	
	pthread_t *threads;

	threads = malloc(Ncust * sizeof(pthread_t));
	if (threads == NULL) {
		printf("NOT ENOUGH MEMORY!\n");
		return -1;
	}

	
   	int threadCount;
	int countArray[Ncust];
   	for(threadCount = 0; threadCount < Ncust; threadCount++) {
		countArray[threadCount] = threadCount + 1;
		/*dimiourgia tou thread*/
    		rc = pthread_create(&threads[threadCount], NULL, pelatis, &countArray[threadCount]);

		/*elegxos oti to thread dimiourgithike swsta.*/
    		if (rc != 0) {
    			printf("ERROR: return code from pthread_create() is %d\n", rc);
       			exit(-1);
       		}
    	}

	void *status;
	
	for (threadCount = 0; threadCount < Ncust; threadCount++) {
		rc = pthread_join(threads[threadCount], &status);
		
		if (rc != 0) {
			printf("ERROR: return code from pthread_join() is %d\n", rc);
			exit(-1);		
		}
	}

	for(int k =0 ; k < NzoneA + NzoneB + NzoneC;k++){
		for(int n =0; n < Nseat; n++){
			if(theatre_plan[k][n] != -10){
				printf("Row %d Seat %d / Customer %d\n",k+1 , n+1,theatre_plan[k][n]);
			}
		}
	}
	printf("----------------------------------------------------------------------\n");
	printf("Total profits from sales: %d eyrw.\n",bank_account);
	printf("Time Wait Per Costumer: %.2f \n",time_wait/(double)N);
	printf("Time Service Per Costumer: %.2f \n",time_service/(double)N);
	printf("----------------------------------------------------------------------\n");


    	pthread_mutex_destroy(&countMutex);
	
 	rc = pthread_cond_destroy(&countThresholdCondition);
	
    	pthread_mutex_destroy(&basicmutex);
	

	pthread_mutex_destroy(&timemutex);

	pthread_mutex_destroy(&Zonemutex);

	pthread_mutex_destroy(&cashierMutex);

	rc = pthread_cond_destroy(&countCashierCondition);
	
	free(threads);

	return 1;
}
