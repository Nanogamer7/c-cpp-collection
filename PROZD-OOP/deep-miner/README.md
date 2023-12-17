`docs/html/index.html` for auto generate docs (only diagrams)
`docs/diagrams/classes.svg` for full uml-diagram

## Spielregeln

### Die Idee
Du bist ein Roboter, mit der Aufgabe Erdgas zu sammeln. Erdgas steigt zwar auf, jedoch nur langsam und unregelmäßig, und dein Bohrer kann nicht besonders tief bohren. Du musst daher geschickt die Stellen mit dem meisten Erdgas anbohren, was jedoch dadurch erschwert wird, dass dein Scanner schwach ist. Das Gelände ist außerdem sehr uneben; es kann passieren, dass du stecken bleibst, oder gar abrutscht.

### Das Feld
Das 5x5 Spielfeld ist zufällig generiert, in jedem Feld sind 10 Blöcke mit einer unterschiedlichen Menge an Erdgas.

### Bewegung
Bewegen kostet zwei Treibstoff pro Feld; solang ein Roboter genügend Treibstoff hat, kannst er sich auf jedes freie Feld bewegen. Auf einem Feld kann jeweils nur ein Roboter stehen. Kann sich ein Roboter nicht mehr bewegen, scheidet er aus (selbst wenn blockierte Felder wieder frei werden könnten).
Achtung: Da das Gelände zu instabil ist, ist es ein zu großes Sicherheitsrisiko stehen zu bleiben. Jeder Roboter muss dich daher in jeder Runde bewegen.

### Bohren
Jedes Feld wird von oben anbohren, um je nach Bohrer ein oder mehrere *Blöcke* Erdgas abzubauen. Das Erdgas wird zur Punktezahl des jeweiligen Roboter gezählt, und je nach Ausrüstung wird ein gewisser Teil davon zu Treibstoff verarbeitet. Bevor ein Roboter bohrt, verwendet außerdem seine Fähigkeit.

### Fallen
Auf manchen Feldern befinden sich fallen. Diese werden ausgelöst, sobald sich ein Roboter auf das Feld bewegt - selbst wenn die Falle nicht direkt an der Oberfläche befindet. Löst ein Roboter eine Falle aus, kann er keine weitern in der selben Runde auslösen. Es gibt folgende Fallen:

 - **Defekt** (-1): Dein Bohrer bleibt stecken. Du darfst diese Runde keinen Wert abbauen.
 - **Erdrutsch** (-2): Du rutsch ab und landest auf einer niedrigeren (wortwörtlich) Stelle.
 - **Leck** (-3): Dein Treibstofftank hat einen Leck. Due verlierst einen Teil deines Treibstoff.

### Instabilität
Durch das extrahieren von Erdgas kann es passieren, dass sich das ganze Gelände bewegt. Jedes mal wenn ein Roboter ein vielfaches von 50 erreicht, passiert so ein *Shift*.

### Spielende
Das Spiel endet, sobald sich kein Roboter mehr bewegen kann, oder keine Erdgas mehr vorhanden ist[^1]. Gewinnen tut der Roboter mit der höchsten Punktezahl.

[^1]: Das Erdgas zählt als aufgebraucht, sobald keine Blöcke mehr vorhanden sind. Die tatsächlichen Werte sind dabei irrelevant.

## Roboter

 - **Deep**: Deep hat keine besonderen Fähigkeiten, bohrt aber zwei Blöcke tief.
 - **Pump**: Pump sortiert alle Blöcke im aktuellen Feld, bevor er den obersten Block abbaut
 - **Filter**: Filter bewegt von jedem Block ein Gas an die Oberfläche



## Class and file structure

`deep-miner.cpp` main: manages menu, creates characters incl. abilities and game, calls display functions
`game.cpp` class game: manages characters and calls world functions (turn order, etc.), calls display functions
`ẁorld.cpp` class world: manages world, world generation, etc.
`bot.cpp` class bot: mananges moves, actions, and abilities
`player.cpp` & `computer.cpp` class player & class computer, inherit bot: choose action (user input or AI)
`display.cpp` namespace display: output functions
all other classes are abilities in some form

main creates game, creates bots, calls addBots()
game creates world, calls world-generate functions, calls move() for bots in turn order
world generates grid, manages grid
bot + child class makes decision, calls abilities
abilities modify inputs