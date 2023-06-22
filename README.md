# pagetracer

### О проекте

Загружаемый модуль ядра Linux, который позволяет получать информацию о состоянии физических страниц, выделенных процессу, по его идентификатору. Получаемые данные для каждой страницы состоят из следующих параметров:

* тип страницы;
* количество ссылок на страницу в системе;
* количество записей в таблице страниц, указывающих на страницу.

Модуль написан на языке программирования C, для его сборки используется утилита GNU make.

### Использование

Для сборки модуля необходимо выполнить следующие команды:

```
git clone https://github.com/hamzreg/os-course.git
cd ./os-course/src/
make
```

Для отслеживания состояний физических страниц процесса с идентификатором *a* необходимо загрузить модуль с помощью следующей команды:

```
make load pid=a
```

Получить сведения о состоянии физических страниц процесса с идентификатором *a* можно, используя следующую команду:

```
make log pid=a
```

В результате будут выведены сообщения системного журнала, содержащие описанные параметры физических страниц процесса с идентификатором *a*.

Для выгрузки модуля необходимо выполнить следующую команду:

```
make unload
```

### Документация

* [расчетно-пояснительная записка](https://drive.google.com/file/d/19z0J9cRtLQk6l1yoA2Z_LAl3j-Lr_Etd/view?usp=sharing "расчетно-пояснительная записка").

```
Разработано в рамках курсовой работы по курсу "Операционные системы"
7 семестр ИУ7, МГТУ им. Н. Э. Баумана, 2023.
```