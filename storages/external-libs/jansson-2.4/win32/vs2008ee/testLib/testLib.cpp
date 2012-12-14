// testLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <jansson.h>
using namespace std;
//Like all the programs using Jansson, we need to include jansson.h.
//The following definitions are used to build the GitHub API request URL:

#define URL_FORMAT   "https://api.github.com/repos/%s/%s/commits"
#define URL_SIZE     256
/* Return the offset of the first newline in text or the length of
   text if there's no newline */
static int newline_offset(const char *text)
{
    const char *newline = strchr(text, '\n');
    if(!newline)
        return strlen(text);
    else
        return (int)(newline - text);
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Десереализация
	size_t i;
    char url[URL_SIZE];

    json_t *root;
    json_error_t error;
	
	// В примере делается запрос, но пока так делать не будем
	//snprintf(url, URL_SIZE, URL_FORMAT, argv[1], argv[2]);
	//This uses the URL_SIZE and URL_FORMAT constants defined above. Now we’re ready to actually request the JSON data over the web:
	//text = request(url);

	string text = "[\
	{\
    \"url\": \"https://api.github.com/repos/octocat/Hello-World/commits/6dcb09b5b57875f334f61aebed695e2e4193db5e\",\
    \"sha\": \"6dcb09b5b57875f334f61aebed695e2e4193db5e\",\
    \"commit\": {\
      \"url\": \"https://api.github.com/repos/octocat/Hello-World/git/commits/6dcb09b5b57875f334f61aebed695e2e4193db5e\",\
      \"sha\": \"6dcb09b5b57875f334f61aebed695e2e4193db5e\",\
      \"author\": {\
        \"name\": \"Monalisa Octocat\",\
        \"email\": \"support@github.com\",\
        \"date\": \"2011-04-14T16:00:49Z\"\
      },\
      \"committer\": {\
        \"name\": \"Monalisa Octocat\",\
        \"email\": \"support@github.com\",\
        \"date\": \"2011-04-14T16:00:49Z\"\
      },\
      \"message\": \"Fix all the bugs\",\
      \"tree\": {\
        \"url\": \"https://api.github.com/repos/octocat/Hello-World/tree/6dcb09b5b57875f334f61aebed695e2e4193db5e\",\
        \"sha\": \"6dcb09b5b57875f334f61aebed695e2e4193db5e\"\
      }\
    },\
    \"author\": {\
      \"login\": \"octocat\",\
      \"id\": 1,\
      \"avatar_url\": \"https://github.com/images/error/octocat_happy.gif\",\
      \"gravatar_id\": \"somehexcode\",\
      \"url\": \"https://api.github.com/users/octocat\"\
    },\
    \"committer\": {\
      \"login\": \"octocat\",\
      \"id\": 1,\
      \"avatar_url\": \"https://github.com/images/error/octocat_happy.gif\",\
      \"gravatar_id\": \"somehexcode\",\
      \"url\": \"https://api.github.com/users/octocat\"\
    },\
    \"parents\": [\
      {\
        \"url\": \"https://api.github.com/repos/octocat/Hello-World/commits/6dcb09b5b57875f334f61aebed695e2e4193db5e\",\
        \"sha\": \"6dcb09b5b57875f334f61aebed695e2e4193db5e\"\
      }\
    ]\
  }\
]";

	root = json_loads(text.c_str(), 0, &error);
	if(!json_is_array(root)) {
		fprintf(stderr, "error: root is not an array\n");
		return 1;
	}

	// обработка
	json_t *data, *sha, *commit, *message, *id;
	for(i = 0; i < json_array_size(root); i++) {
		const char *message_text;

		data = json_array_get(root, i);
		if(!json_is_object(data))
		{
			fprintf(stderr, "error: commit data %d is not an object\n", i + 1);
			return 1;
		}
		
		// отдельно
		sha = json_object_get(data, "sha");
		if(!json_is_string(sha)) {
			fprintf(stderr, "error: commit %d: sha is not a string\n", i + 1);
			return 1;
		}

		commit = json_object_get(data, "commit");
		if(!json_is_object(commit)) {
			fprintf(stderr, "error: commit %d: commit is not an object\n", i + 1);
			return 1;
		}

		message = json_object_get(commit, "message");
		if(!json_is_string(message)) {
			fprintf(stderr, "error: commit %d: message is not a string\n", i + 1);
			return 1;
		}

		/*id = json_object_get(data, "id");
		if(!json_is_string(id)) {
			fprintf(stderr, "error: commit %d: message is not a string\n", i + 1);
			return 1;
		}*/

		message_text = json_string_value(message);
		printf("%.*s\n",
			   newline_offset(message_text),
			   message_text);
	}
	//json_decref(root);

	// Сереализация
	json_t *pObj = json_pack ("{s:i, s:s}", "foo", 1, "bar", "string"); 
    string result( json_dumps(commit, JSON_INDENT(2)) );
	cout << result << endl;
	return 0;
}

