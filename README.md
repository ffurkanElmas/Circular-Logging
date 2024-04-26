Circular Logging

*Programın çalışması için:
config.json dosyasının konumu ve log dosyalarının oluşturulacağı klasörün konumu yapıcı metotta belirtilmelidir.

*config.json dosyası ayarları:
creation_rate : Oluşturma sıklığı (Tam sayı Olmalı.)
log_type : "second", "minute", "hour", "day" bu dördünden birisi yazılmalı.
max_files : Oluşturulacak maksimum dosya sayısı (Tam sayı olmalı.)

*Programın çalışma mantığı:
Config dosyasından çekilen ayarlar ile istenilen sıklıkta loglama yapar. Ve maksimum dosya sayısı belirtilebilir maksimum dosya sayısı aşıldıkça en eski dosya silinir.

