![Static Badge](https://img.shields.io/badge/License-MIT-green)
![Simple-BlackJack](https://socialify.git.ci/Flapjacck/Simple-BlackJack/image?description=1&descriptionEditable=Game%20of%20Blackjack%20made%20in%20the%20C%20programming%20language.%20Created%20to%20deepen%20my%20understanding%20of%20the%20C%20language%20and%20git.&language=1&name=1&pattern=Plus&stargazers=1&theme=Dark)



## Screenshots

![App Screenshot](https://i.imgur.com/jHoLb1J.png)


## Installation Using Terminal

*****Need C compiler installed prior to install (I use [tdm-gcc](https://jmeubank.github.io/tdm-gcc/))***

1. Clone the project to desired location:
```bash
  git clone https://github.com/Flapjacck/Simple-BlackJack.git
```

2. Change directory to inside "\Simple-BlackJack\\" folder:
```
  cd simple-blackjack
```

3. Run the make file to compile the program:
```
  make
```

4. Open "*SimpleBJ.exe*" to run the program

- The "*score.txt*" file location is offset if you are on Mac. To fix this replace the line with your local "*score.txt*" file path:
```
Line 52 | Replace "simple-blackjack/score.txt" with (EX. "Desktop/Simple-BlackJack/Simple-BlackJack/score.txt")
```

## How to Play BlackJack

- Player attempts to beat the dealer by getting a count as close to 21 as possible, without going over 21 or having a higher count than the dealer
- Dealer stands on 17 - 21
- Instant win when Player is dealt six cards
- Player win pays 1:1 | Natural BlackJack pays 3:2 | Insurance pays 2:1

## F.A.Q

Q: Make file gives a error "#include <windows.h> not found"

A: Most likely your on Mac and havent deleted the necessary code (check instalation step #3)

   
## Authors

- [@Flapjacck](https://www.github.com/Flapjacck) | If you have any feedback, please reach out to me on my [X](https://x.com/SpennGK)
- [@boomboom135](https://www.github.com/boomboom135)
