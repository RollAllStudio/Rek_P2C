# \##################################

# \### Readme TPP\_Multi prototype ###

# \##################################

# 

# \### Jak grać ###

# 

# 

# \### Main menu

# Po uruchomieniu gry wyświetlane jest menu główne. Tutaj gracz ma możliwość utworzyć serwer, lub dołączyć do istniejącego serwera.

# Aby dołączyć do istniejącego serwera, gracz musi w pierwszym polu tekstowym po lewej stronie menu wpisać swój nick.

# Aby utworzyć własny serwer, poza wpisaniem swojego nick-u gracz musi wpisać również nazwę serwera ( drugie pole tekstowe ) - następnie kliknąć guzik Host Game.

# 

# Do istniejącego serwera można dołączyć kiedy wyświetli się on w liście w prawej stronie menu - należy kliknąć przycisk join server.

# Lista serwerów odświeżana jest automatycznie.

# 

# \### Lobby

# Po utworzeniu serwera, lub dołączeniu do istniejącego gracz przechodzi do lobby.

# Tutaj może wybrać postać, którą będzie grać. Kiedy będzie gotowy do gry musi kliknąć przycisk ready ( w dolnej części lobby ).

# Po kliknięciu guzika, w liście graczy obok tego gracza pojawi się zielona ikona - kliknięcie guziku ponownie oznacza, że gracz zmienił zdanie i nie jest jednak gotowy do startu rozgrywki.

# 

# Klient ma w lobby również przycisk leave server - który pozwala mu opuścić serwer.

# Host ma w lobby dwa dodatkowe przyciski:

# Start match - rozpoczyna rozgrywkę, wszyscy gracze muszą mieć zaznaczone ready.

# Close Server - wyłącza serwer

# Host może w lobby ustawić dodatkowo ilość zabójstw potrzebną do tego, aby któryś z graczy wygrał mecz

# 

# \### Lobby | Postaci

# Gracze mogą wybrać jedną z dwóch postaci:

# \# Knight - postać walcząca mieczem

# \# Wizard - postać walcząca zaklęciem kuli ognia

# 

# \### Rozgrywka

# Kiedy wszyscy gracze są gotowi i host kliknie start match gracze przenoszeni są na poziom rozgrywki.

# 

# \### Rozgrywka | Input

# \# WSAD - poruszanie postacią

# \# Oś XY myszy - poruszanie kamerą

# \# Lewy przycisk myszy - atak

# \# Tab - wyświetlenie tablicy wyników

# \# Tab + ESC - ( klient ) wyjście z serwera / ( Host ) wyłączenie serwera

# 

# \### Rozgrywka | Ataki

# Wykonanie ataku ma trzy warunki

# \# Postać gracza musi być żywa ( mieć życie większe od 0 )

# \# Postać gracza nie może aktualnie wykonywać ataku

# \# Postać gracza musi mieć odpowienią ilość zasobu wykorzystywanego do ataku ( mana dla postaci Wizard, stamina dla postaci Knight )

# 

# \### Rozgrywka | Pickup

# Na środku poziomu rozgrywki co okreslony czas ( 25 sekund ) pojawia się pickup, który podniesiony przez gracza przywraca mu życie

# 

# \### Struktura projektu ###

# 

# \### Moduły

# 

# Projekt podzielony jest na moduły.

# Między modułami dopuszczalne są tylko dwie zależności : 

# Moduły silnika -> Dowolny moduł projektu

# Dowolny moduł projektu -> moduł główny

# 

# Lista modułów : 

# \###	TPP\_Multi

# Moduł główny. Łączy wszystkie moduły, implementuje podstawowe klasy gameplayowe oraz klasy UI

# \###	Actions

# Moduł implementuje mechanikę akcji, które mogą być odgrywane w postaciach.

# \### Dynamic mesh spawner

# Moduł implementuje mechanikę, która pozwala na przypisanie do dowolnego scene component w aktorze przypisać gameplay tag, oraz dodawać static mesh componenty do aktora ( również z przypisanym tagiem )

# \### Multiplayer Game

# Moduł implementuje klasy zarządzające sesją sieciową, oraz podstawowe klasy zarządzające serwerem - logowanie graczy, przechowywanie informacji o statystykach czy identyfikacji graczy

# \### Resource Component

# Moduł implementuje mechanikę "zasobów" aktora - wykorzystywany jest do implementacji życia, many oraz staminy postaci.

# \### Spell projectile

# Moduł implementuje klasy odpowiedzialne za konfigurację zaklęć, oraz spawn pocisków zaklęć

# 

# \### Optymalizacja ruchu sieciowego

# \# W miejscach w których to możliwe replikacja odbywa się z pominięciem Ownera ( DOREPLIFETIME\_CONDITION - z warunkiem SKIP\_OWNER )

# \# Wygląd postaci oraz jego klasa animacji nie jest przesyłany przez referencję do assetu, tylko przez referencję do wiersza z bazy danych postaci,

# jeszcze na etapie lobby - dzięki temu każdy klient wie jakie assety przypisać do aktora postaci każdego gracza, bez replikacji assetów czy wysyłania ich przez RPC

# 

# \### Optymalizacja animacji

# \# W skeletal meshu postaci gracza ustawione jest tickowanie tylko montages, jeżeli postać nie jest renderowana - montage muszą tickować, aby wyzwalać anim notify, które odpowiedzialne są

# między innymi za spawnowanie pocisków zaklęć lub uruchamianie kolizji ataków melee.

# \# Anim graph w ABP postaci pobiera wartości przez thread safe access

# 

# \### Stałe systemowe

# Wszystkie stałe systemowe przechowywane są w klasach konfiguracyjnych - nie stosujemy magicznych liczb ( stałych w kodzie ) - poza wartościami silnikowymi ( np. podstawowe silnikowe profile kolizji )

# Klasy konfiguracyjne opisane są w dziale konfiguracja rozgrwki.

# 

# \### Regiony

# Część klas dla większej czytelności podzielona jest na regiony - lub część kodu jest ukryta w regionach.

# Aby uniknąć nieoczekiwanej zmiany dostępności metod oraz zmiennych w klasie, dla regionów zastosowana jest zasada zamykania dostępności w zakresie regiony - nawet

# jeżeli dyryktywy dostępności są przez IDE oznaczone jako kod zbędny. Tz. jeżeli region ma zacząć się od wartości private, to nawet jeżeli nad regionem wartości są już oznacozne

# jako private, to region i tak sam dodaje dyrektywe dostępności private.

# 

# \### Gettery

# Proste gettery ( takie, które tylko zwracają wartość, a nie np. wyszukują ją w tablicy, są definiowane inline w headerze ).

# 

# \### Funkcje Find

# Gettery, które przeszukują tablice / mapy, aby wyszukuać jakąś wartość, ktorej może tam nie być, zawsze zwracają wartość typu bool jako podstawową wartość funkcji

# ( to pozwala na proste umieszczanie tych funkcji jako warunek w if-ie ) a samą wyszukiwaną wartość zwracają parameterm.

# Takie funkcje, jeżeli są funkcjami z dostępem z blueprintów, nie mogą być BlueprintPure, tylko BlueprintCallable - funkcje pure wyzwalane są wielokrotnie w blueprincie, jeżeli

# mają dwie wartości wyjściowe i chcemy pobrać obie.

# 

# \### Konfiguracja rozgrywki ###

# 

# \## Pickupy

# Na poziomie można umieścić pickup, wybierając dodawanie aktorów w górnym pasku edytora i wyszukując klase pickup

# Po umieszczeniu pickupu na poziomie należy ustawić w nim static mesh ( dziedziczy ze static mesh actor ) oraz tag akcji jaką wyzwoli w graczu ( zmienna Pickup Action )

# Po umieszczeniu pickupu na poziomie można w nim zmienić jego respwan time ( zmienna Respawn Time )

# 

# \## Project settings

# Do project settings dodane są dwie zakładki 

# 

# \# Multiplayer Game Constants

# &nbsp;	Max Session Name Len - maksymalna długość nazwy serwera jaką może wpisać gracz

# &nbsp;	Max Player Name Len - maksymalna długość nick-u jaką może wpisać gracz

# &nbsp;	Max Public Connections - maksymalna ilość graczy, jaka może połączyć się do jednego serwera

# &nbsp;	Max Sessions Find - maksymalna ilość serwerów jaka wyświetli się w wyszukiwarce serwerów

# &nbsp;	Lobby World - Poziom na który przenoszeni są gracze w lobby

# &nbsp;	Session destroyed return World - Poziom na który przenoszeni są gracze kiedy sesja zostanie wyłączona / odłączą sie od sesji

# &nbsp;	Server player data class - Klasa instancji obiektu, który opisuje dane gracza na serwerze

# &nbsp;	DefaultWinConditions - Domyślne warunki zwycięstwa

# &nbsp;	

# \# Game Constants

# &nbsp;	Spell Target Trace Len - długość raycastu, który wyszukuje gdzie gracz celuje aby znaleźć kąt nachylenia pocisku zaklęcia

# &nbsp;	Respawn Time - ilość czasu do respawnu gracza po śmierci	

# &nbsp;		#Cat - Match

# &nbsp;		Match World - Poziom na który gracze są przenoszeni w trakcie rozgrywki

# &nbsp;		FinishMatchWidgetDisplayTime - Czas wyświetlania ekranu końca meczu, po zwycięstwie jakiegoś gracza

# &nbsp;		#Cat - Camera

# &nbsp;		Camera boom len - długość spring arm-u kamery gracza

# &nbsp;		Camera boom offset - relatywny transform spring arm-u kamery gracza

# &nbsp;		Camera Boom Probe Channel - trace channel spring arm-u kamery gracza

# &nbsp;		#Cat - Input

# &nbsp;		Default Mapping Context - Domyslny mapping context

# &nbsp;		Input Actions - Przypisane do gameplay tagów input actions

# &nbsp;		Camera Pitch Limit - Zakres możliwości poruszania kamerą w osi Y

# &nbsp;		#Cat - UI

# &nbsp;		Main Menu Widget Class - Klasa widgetu main menu

# &nbsp;		Lobby Widget Class - Klasa widgetu lobby

# &nbsp;		Session Join Widget Slot Class - Klasa widgetu slotu serwera

# &nbsp;		Lobby Player Widget Slot Class - Klasa widgetu slotu gracza w lobby

# &nbsp;		Character Slot Widget Class - Klasa widgetu slotu postaci w wyborze postaci

# &nbsp;		Match player HUD widget Class - Klasa widgetu HUDu gracza

# &nbsp;		Scoreboard slot widget class - Klasa widgetu slotu gracza w tablicy wyników

# &nbsp;		

# \## Baza danych

# 

# \# DT\_Characters ( Content/TPPMulti/DataBase/Characters/DT\_Characters ) Baza danych postaci, które są możliwe do wyboru w lobby

# &nbsp;	Wiersz przechowuje

# &nbsp;		Mesh - Skeletal mesh postaci

# &nbsp;		Mesh Offset - Relatywny transform komponentu skeletal mesha w klasie postaci ( względem roota, czyli kapsuły )

# &nbsp;		Anim Instance - Klasa anim bluepritnu postaci

# &nbsp;		Actions Collection - Data asset z akcjami możliwymi do wykonania przez postać

# &nbsp;		Dynamic meshes - Mapa opisująca dynamiczne meshe do spawnu w postaci - kluczem mapy jest gameplay tag mesh-a a wartością data asset typu Dynamic mesh config

# &nbsp;		Spell Spawn Socket - Socket w szkielecie postaci, w którym będzie spawnowany pocisk zaklęcia

# &nbsp;		Resources Data - Mapa opisująca wartości zasobów postaci - klucz to gameplay tag zasobu a wartość to wartość inicjalizacji zasobu

# &nbsp;		Damage Collider Radius - Szerokość kapsuły damage collidera dla ataków melee

# &nbsp;		Damage Collider Half Height - Połowa wysokości kapsuły damage collidera dla ataków melee

# &nbsp;		Damage Collider Profile Name - Nazwa profilu kolizji damage collidera dla ataków melee

# &nbsp;		Damage Collider Attach Socket - Nazwa socketu w meshu broni ( spawnowany z dynamic mesh spawnera ) do którego będzie attachowany damage collider dla ataków melee

# &nbsp;		Damage Collider Offset - Offset damage collidera ataków melee względem attachowanego socketu

# &nbsp;		

# &nbsp;		Display Name - nazwa wyświetlana postaci w UI

# &nbsp;		Dispaly Iamge - brush ikony postaic w UI

# &nbsp;		

# WSZYSTKIE WARTOŚCI PONIŻEJ MOGĄ BYĆ ZMIENIANE W TRAKCIE Play In Editor

# &nbsp;		

# \# Akcje - Data assety typu ActionsCollection - przechowywane w folderze Content/TPPMulti/DataBase/Actions

# &nbsp;	Asset przechowuje mapę, której kluczem jest gameplay tag akcji a wartością obiekt definicji akcji

# \## Definicje akcji: 

# &nbsp;	#Base ( wszystkie definicje z tego dziedziczą , klasa abstarkcyjna )

# &nbsp;		Condition - obiekt warunku odegrania akcji - brak przypisania, to brak warunków ( zawsze true )

# &nbsp;		Success Event - obiekt eventu, który odgrywany jest kiedy akcja może zostać odegrana ( może być nullptr )

# &nbsp;		Action Stack - Blokowany stack w actions componencie - na czas odgrywania akcji

# &nbsp;		Stack Locks - Mapa, która definiuje dodatkowe blokady staków w actions componencie - klucz to gameplay tag stacku, a wartość to czas blokady ( ustawienie wartości na mniejszą lub równą 0, blokuje stack do czasu ręcznego odblokowania )

# &nbsp;	

# &nbsp;	# Play montage ( Akcja odegrania anim montage )

# &nbsp;		Montage to play - montage do odegrania

# &nbsp;		Play Rate - Skala prędkości odgrywania montage

# &nbsp;		

# &nbsp;	# Action Definition Play Niagara Attached

# &nbsp;		System to Play - System niagary do odegrania

# &nbsp;		Lock Stack Time - nadpisana wartość blokowania głównego stacku akcji

# &nbsp;		

# \## Warunki odegrania akcji

# &nbsp;	#Base ( wszystkie warunki z tego dziedziczą , klasa abstarkcyjna - nie implementuje konfiguracji, tylko metody )

# &nbsp;	

# &nbsp;	# Composite ( pozwala na przypisanie kilku warunków )

# &nbsp;		Elements - Elementy composite

# &nbsp;		

# &nbsp;	# Action Execute Condition Resource ( warunek, że postać posiada zasoby )

# &nbsp;		Resource Tag - Gameplay tag zasobu

# &nbsp;		Min Resource Value - Minimalna wartość zasobu

# &nbsp;		

# \## Success Eventy 

# &nbsp;	#Base ( wszystkie eventy z tego dziedziczą , klasa abstarkcyjna - nie implementuje konfiguracji, tylko metody )

# &nbsp;	

# &nbsp;	# Composite ( pozwala na przypisanie kilku eventów )

# &nbsp;		Elements - Elementy composite

# &nbsp;	

# &nbsp;	# Action Success Event Consume Resource ( pobiera zasób z postaci )

# &nbsp;		Resource Tag - gameplay tag zasobu

# &nbsp;		Value to consume - Wartośc zasobu do odebrania

# &nbsp;		

# &nbsp;		# Action Success Event Add Resource ( dodaje zasób postaci )

# &nbsp;		Resource Tag - gameplay tag zasobu

# &nbsp;		Value to Add - Wartośc zasobu do dodania

# &nbsp;		

# &nbsp;	# Action Success Event Set Melee Damage ( ustawia damage oraz typ obrażeń w damage colliderze postaci )

# &nbsp;		Damage To Set - Ilość DMG do ustawienia

# &nbsp;		Damage Type - Klasa typu obrażeń do ustawinia

# &nbsp;		

# \# Dynamic Meshes - Data asesty typu DynamicMeshConfig - przechowywane w folderze Content/TPPMulti/DataBase/DynamicMeshes

# &nbsp;	Przechowuje wartości opisujące meshe dodatkowe do spawnu w postaci

# &nbsp;		Mesh - Static mesh do spawnu

# &nbsp;		Attach Location Rule / Attach Rotation Rule / Attach Scale Rule / Weld simulated bodies - Zasany attachmentu komponentu mesha

# &nbsp;		Attach Socket - Soket w szkielecie postaci, do którego mesh zostanie attachowany

# &nbsp;		Transofrm Offset - Offset względem socketu

# &nbsp;		ParentTag - Gameplay tag scene komponentu, do którego zostanie attachowany ten mesh - musi być wcześniej ustawione w kodzie

# 

# \# Spells - Data assety typu SpellConfig - przechowywane w folderze Content/TPPMulti/DataBase/Spells

# &nbsp;	Opisuje wartości, które konfigurują pocisk zaklęcia

# &nbsp;		Fly Niagara System - System cząsteczkowy, który jest wykonywany w trakcie lotu pocisku

# &nbsp;		Hit Niagara System - System cząsteczkowy, który jest wykonywany kiedy pocisk w coś uderzy

# &nbsp;		Speed - prędkośc pociku

# &nbsp;		Size - Wielkosć sfery kolizji pocisku

# &nbsp;		Damage - Obrażenia pocksu

# &nbsp;		Damage radius - wielkość sfery, która określa "wybuch" pocisku - czyli jak daleko od trafienia zadane zostaną obrażenia ( ustawienie na mniej lub równe 0 powoduje, że obrażania zadane są tylko trafionemu aktorowi )

# &nbsp;		Damage Type - klasa typu zadanych obrażeń

# &nbsp;		Projectile Collision Profile - Nazwa profilu kolizji pocisku

# &nbsp;		Hit Overlap Profile Name - Profil kolizji wykorzystywany przy wyszukiwaniu aktorów do zadania obrażeń, jeżeli obrażenia zadawane są dystansowo ( Damage Radius > 0 )

