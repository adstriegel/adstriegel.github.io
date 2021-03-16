
pthread_mutex_t   theMutex;
int   g_nCount_Goats = 0;
int   g_nCount_Chickens = 0;

pthread_cond_t    condGoats;
pthread_cond_t    condChickens;

#define MAX_GOATS 3

void chicken_enter ()
{
  pthread_mutex_lock(&theMutex);

  // If there are any goats -- no go
  while(g_nCount_Goats > 0)
  {	  
	  pthread_cond_wait(&condChickens,&theMutex);
  }

  // We know here that we only got here if
  //  1) We have the mutex
  //  2) There are no goats in the barn

  g_nCount_Chickens++;
  pthread_mutex_unlock(&theMutex);
}

void goat_enter ()
{
  pthread_mutex_lock(&theMutex);

  // Only go in if there are less than 3 goats and no
  //  chickens

  while(g_nCount_Goats >= MAX_GOATS || g_nCount_Chickens > 0)
  {
    pthread_cond_wait (&condGoats, &theMutex);
  }

  // We know that we only got here if
  //  1) We have the mutex
  //  2) The numbers of goats is less than MAX_GOATS
  //  3) There are no chickens in the barn

  g_nCount_Goats++;
  pthread_mutex_unlock(&theMutex);
}


void chicken_leave ()
{
  pthread_mutex_lock(&theMutex);
  g_nCount_Chickens--;

  if(g_nCount_Chickens == 0)
  {
	/* Wake up all of the goats that might be waiting */
    pthread_cond_broadcast(&condGoats);
  }

  // No need to signal the chickens as they could have come in
  // at any time
  pthread_mutex_unlock(&theMutex);
}


void goat_leave ()
{
  pthread_mutex_lock(&theMutex);

  g_nCount_Goats++;

  if(g_nCount_Goats == 0)
  {
    /* Wake up any waiting chickens */
    pthread_cond_broadcast(&condChickens);
  }
  else
  {
    /* We have one more space for goats */
    pthread_cond_signal(&condGoats);
  }

  pthread_mutex_unlock(&theMutex);
}

