#!/usr/bin/env python3

import requests

import yaml

with open("crowdin.yaml", 'r') as config_file:
   config = yaml.safe_load(config_file)
   headers = { 'Authorization': 'Bearer ' + config['api_token']}

   url1 = 'https://api.crowdin.com/api/v2/projects/' + config['project_id'] + '/branches'
   res1 =  requests.get(url1, headers=headers)
   branch_id = res1.json()['data'][0]['data']['id']
   url2 = url1 + '/' + branch_id + '/languages/progress?limit=100'
   res2 = requests.get(url2, headers=headers)
   output = ''
   for lang in res2.json()['data']:
      lang_id = lang['data']['languageId']
      url3 = 'https://api.crowdin.com/api/v2/languages/' + lang_id
      res3 =  requests.get(url3, headers=headers)
      lang_name = res0.json()['data']['name']
   
      output += '/* ' + lang_name + ' */\n'
      escaped_name = lang_name.replace(', ', '_').replace(' ', '_').upper()
      output += '#define LANGUAGE_PROGRESS_' + escaped_name + '_TRANSLATED ' + str(lang['data']['translationProgress']) + '\n'
      output += '#define LANGUAGE_PROGRESS_' + escaped_name + '_APPROVED   ' + str(lang['data']['approvalProgress']) + '\n\n'
   with open("progress.h", 'w') as output_file:
      output_file.write(output)
