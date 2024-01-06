import serial, time, curses

def send(screen, s, string, y):
    t_time, t_count = 0, 0
    rows, cols = screen.getmaxyx()

    for idx, char in enumerate(string):
        char = char.to_bytes(1, byteorder='big')
        ti1 = time.time()
        s.write(char)        
        s.flush()
        elapsed_time = time.time() - ti1
        t_time = t_time + elapsed_time
        t_count = t_count + 1
        screen.addch(idx // cols, idx % cols, char.decode('utf-8'), curses.color_pair(1))
        screen.addstr(y, 0, f"TX Rate: {round(8 / elapsed_time, 4)} bps | Average bps: {round(t_count * 8 / t_time, 4)}      ")
        screen.refresh()

    s.write(b'\n')
    s.flush()


def main(stdscr):
    curses.curs_set(0)
    stdscr.clear()

    curses.init_pair(1, curses.COLOR_CYAN, curses.COLOR_BLACK)
    curses.init_pair(2, curses.COLOR_GREEN, curses.COLOR_BLACK)
    curses.init_pair(3, curses.COLOR_RED, curses.COLOR_BLACK)

    rows, cols = stdscr.getmaxyx()
    
    to_send = open('tosend.txt', 'rb').readlines()
    stdscr.addstr(to_send[0])

    y, x = stdscr.getyx()

    stdscr.addstr(y + 2, 0, "Status: Sending data")
    stdscr.refresh()

    s = serial.Serial('/dev/ttyUSB1', baudrate=2400)
    time.sleep(2)
    send(stdscr, s, to_send[0], y + 3)

    stdscr.addstr(0, 0, to_send[0])
    stdscr.addstr(y + 2, 0, "Status: Recieving data")
    stdscr.refresh()

    recieved_data = ''

    t_time, t_count = 0, 0

    while True:
        ti1 = time.time()
        d = s.read()
        elapsed_time = time.time() - ti1

        t_time = t_time + elapsed_time
        t_count = t_count + 1

        stdscr.addch((t_count - 1) // cols, (t_count - 1) % cols, d.decode('utf-8'), curses.color_pair(2))
        stdscr.addstr(y + 4, 0, f"RX Rate: {round(8 / elapsed_time, 4)} bps | Average bps: {round(t_count * 8 / t_time, 4)}      ")
        stdscr.refresh()

        if d == b'\n':
            break

        try:
            recieved_data = recieved_data + d.decode('utf-8')
        except:
            pass

    stdscr.move(y + 2, 0);
    stdscr.clrtoeol();
    
    if recieved_data == to_send[0].decode('utf-8'):
        stdscr.addstr(y + 2, 0, "Status: Done!", curses.color_pair(2))
    else:
        stdscr.addstr(y + 2, 0, "Status: Recieved Data != Sent Data", curses.color_pair(3))
    stdscr.refresh()

    stdscr.getch()


curses.wrapper(main)