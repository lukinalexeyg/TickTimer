# TickTimer
Класс TickTimer расширяет функционал классов QElapsedTimer и QTimer.
## Возможности:
+ Временная остановка и возобновление работы таймера  
+ Выполнение тиков через заданные промежутки времени  
+ Возможность остановки таймера в момент окончания отведенного времени таймеру или совершении заданного числа тиков  
+ Возможность использования типа таймера ``Qt::TimerType::CoarseTimer``, но со стабилизацией времени между тиками (тип ``TickTimer::CoarseTimerStabilized``). При этом точность между тиками близка точности при использовании типа ``Qt::TimerType::PreciseTimer``)
## Лицензия
Copyright (c) 2018 Alexey Lukin

MIT License. See LICENSE file