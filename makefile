CC := g++-4.8
DD := -std=c++11 -w
bin/main: build/User.o build/Date.o build/Meeting.o build/Storage.o build/AgendaService.o build/AgendaUI.o build/Agenda.o
		$(CC) $(DD) -I./include -o $@ build/User.o build/Date.o build/Meeting.o build/Storage.o build/AgendaService.o build/AgendaUI.o build/Agenda.o
build/User.o: src/User.cpp
	$(CC) $(DD) -I./include -c -o $@ src/User.cpp
build/Date.o: src/Date.cpp
	$(CC) $(DD) -I./include -c -o $@ src/Date.cpp
build/Meeting.o: src/Meeting.cpp
	$(CC) $(DD) -I./include -c -o $@ src/Meeting.cpp
build/Storage.o: src/Storage.cpp
	$(CC) $(DD) -I./include -c -o $@ src/Storage.cpp
build/AgendaService.o: src/AgendaService.cpp
	$(CC) $(DD) -I./include -c -o $@ src/AgendaService.cpp
build/AgendaUI.o: src/AgendaUI.cpp
	$(CC) $(DD) -I./include -c -o $@ src/AgendaUI.cpp
build/Agenda.o: src/Agenda.cpp
	$(CC) $(DD) -I./include -c -o $@ src/Agenda.cpp
clean:
	@rm -rf build/*.o
	@rm -rf bin/main