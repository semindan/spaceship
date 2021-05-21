# APO Semestral project

(we can make a table of contents for easier navigation)

### Prerequisites
1. MZAPO kit (there we can place some link to the documentaion for example)
...
### (Kompilace a spuštění) 
### Installation
Project archive can be downloaded from the website page:  
https://gitlab.fel.cvut.cz/semindan/apo-semestral-project  
After that it's necessary to unzip the archive.

Alternatively, open the terminal and write the following command:  
git clone https://gitlab.fel.cvut.cz/semindan/apo-semestral-project.git  

Then to open the project directory:  
cd apo-semestral-project

### Compilation and execution 
1. Open the terminal and get to the project's directory  
2. Local execution on MZAPO:  
	make & ./spaceship
3. Remote execution (link to the mzapo guide):  
	TARGET_IP=xxx.xxx.xxx.xxx make run

(We need to say something about two versions of display and what flags should be used to configure them)


4. Play! (or something less exciting)


### Ovládání hry

Po prvním spuštění se zobrazí menu. Hráč si vybere stiskem ovladače, co chce otevřít, podle barvy. 

### Controls
Atfer the execution you are presented with the main menu,
where you are able to navigate pushing buttons on the MZAPO's rotary switches.  
Push the blue button to start the game.  
Push the green button to view the scoreboard.  
Push the red button to close the application.  

##### Scoreboard
Rotací modrého ovladače může hráč scrollovat scoreboardem. Stisknutí červeného ovladače vrátí hráče do menu.

##### Scoreboard
Rotate the switch to scroll through the scores of players.  
Push the red button to return to the main menu.

##### Nastavení hry
Ovládání menu nastavení a popis jeho činnosti


##### Game parameters
Before jumping into the action you are able to choose the difficulty of the game(size of gate gaps)
and change the bonus spawn chance(Extra HP).  
Rotate the green switch to change the difficulty.  
Rotate the red switch to change the bonus spawn chance.  
Finally, push the blue button to start the game.

##### Hra
Hráč ovládá hru pomocí dvou ovladačů, modrý pro natočení lodi a zelený pro tah jejích motorů. Aktuální nastavení tahu může hráč zjistil na žlutých LED pod ovladači. Hráčovy životy indikuje levá LED, zelená - maxHP, žlutá 2 hp a červená pro poslední život. Aktuální skóre je pak zobrazeno v levém horním rohu.

#### Game
Increase spaceship's thrust to start moving by rotating the green switch, it's possible to stop the spaceship this way, too!  
Move the spaceship up and down to avoid obstacles and collect bonuses(hearts) by rotating the blue switch.  
Exit the current run by pushing the red button.  


##### Game over obrazovka
Po smrti hráče se zobrazí Game over obrazovka. Hra ukazuje dosažené skóre a čeká na input v podobě stisknutí zeleného ovladače. Následně je hráč vyzván k zadání jména. Znaky ve jméně vybírá pomocí otáčení modrého ovladače a jeho stisknutím znak potvrzuje a znak je přidán do jména. Pokud hráč zadá 16 znaků, či stiskne červený ovladač, hra skóre uloží a vrátí se do menu.

##### Game over screen
After you lose or decide to exit the run you see the game over screen with you score.  
Click the green button to move to the next step.  
Then you are able to write your name down, so it later appears on the scoreboard.  
Rotate the blue switch to select the right character, the selected character has blue color.  
To confirm your choice press the blue button.  
Continue to write your name, the maximum length is 16 characters.  
Exit to the main menu when you are done by pushing the red button or after writing 16 characters the result is saved and you are redirected to the main menu automatically.  


### Schéma aplikace

bude image

### Doku
sem něco technical i guess


### Doku
sem něco technical i guess
