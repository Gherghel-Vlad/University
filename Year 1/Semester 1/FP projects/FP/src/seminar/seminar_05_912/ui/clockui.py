from seminar.seminar_05_912.domain.alarm import alarm
from seminar.seminar_05_912.service.service import alarmClock
import pygame


class ui:
    def __init__(self):
        self._alarm_clock = alarmClock()
        self._alarm_clock.add_alarm(alarm(0, 10, ' wake up!'))

    def start(self):
        # start the module
        pygame.init()
        # add a custom event; 10ms = 1 minute
        CLOCKTICK = pygame.USEREVENT + 1
        # TODO Why does the timer stop after some clicks?
        pygame.time.set_timer(CLOCKTICK, 10)
        current_tick = 0

        for event in pygame.event.get():
            # receive events generated by pygame.time.set_timer(...)
            if event.type == CLOCKTICK:
                print('time is: ' + str(current_tick))

                alarm = self._alarm_clock.tick()
                if not alarm is None:
                    # alarm sounds
                    print(alarm)
                current_tick += 1


clock_ui = ui()
clock_ui.start()
