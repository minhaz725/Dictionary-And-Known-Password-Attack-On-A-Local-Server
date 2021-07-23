#include <stdio.h>
#include <curl/curl.h>

 
int main(void)
{
  CURL *curl;
  CURLcode res;
 
  /* In windows, this will init the winsock stuff */
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* get a curl handle */
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL if that is what should receive the
       data. */
    curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:3000/users/login");
    
    //Set the header, the header content may be different
    struct curl_slist* headerlist = NULL; 
    headerlist = curl_slist_append(headerlist, "Content-Type:application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);  
  
    /* Now specify the JSon POST data */
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\"name\" : \"Minhazur\", \"password\" : \"tim\"}");
 
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    
    // print response
    if(res == CURLE_OK) {
    int response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
    printf(", response code: %d",response_code);
  }
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return 0;
}