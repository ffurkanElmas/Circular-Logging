Circular Logging

*Programın çalışması için:
config.json dosyasının konumu ve log dosyalarının oluşturulacağı klasörün konumu yapıcı metotta belirtilmelidir.

*config.json dosyası ayarları:
creation_rate : Oluşturma sıklığı (Tam sayı Olmalı.)
log_type : "second", "minute", "hour", "day" bu dördünden birisi yazılmalı.
max_files : Oluşturulacak maksimum dosya sayısı (Tam sayı olmalı.)

*Programın çalışma mantığı:
Config dosyasından çekilen ayarlar ile istenilen sıklıkta loglama yapar. Ve maksimum dosya sayısı belirtilebilir, maksimum dosya sayısı aşıldıkça en eski dosya silinir.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

*For the program to function: The location of the config.json file and the location where log files will be created should be specified in the constructor method.

*Settings in the config.json file: 
creation_rate: Creation frequency (Should be an integer.) 
log_type: It should be one of "second", "minute", "hour", "day". 
max_files: Maximum number of files to be created (Should be an integer.)

*Operating logic of the program: Logs at the desired frequency based on the settings retrieved from the config file. And a maximum file count can be specified, as the maximum file count is exceeded, the oldest file is deleted.

