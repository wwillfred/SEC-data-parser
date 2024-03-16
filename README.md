# Corporate Financials Calculator

This project will perform calculations on the financial information of publicly traded companies. Example calculations will include averaging a company's return on invested capital (ROIC) over a given number of years, screening for companies that have not had an unprofitable quarter in the last given number of years, and calculating a company's price per a given number of years' average Net Income.

Although such a tool will not be able to identify companies worth investing in, the intent is that this project will help the user identify companies worth doing more in-depth research on as potential investment targets.

I'm making this project in C because I want to learn C. I've chosen the [json-c package][json-c] package for parsing SEC data and [SQLite][sqlite] for structuring data for calculations.

This project uses [Doxygen][doxygen] to generate documentation.

Financial information is sourced from [EDGAR APIs][EDGAR_APIs], specifically the "Bulk data" section.


## Prerequisites
### Install json-c
See the [json-c homebrew page][json-c_homebrew].

```shell
brew install json-c
```

### SQLite

SQLite is included with Mac OS. To confirm you have it installed, run:
```shell
sqlite3
# ctrl-c twice to exit
```

### Doxygen
To install Doxygen on Mac OS:
```shell
brew install doxygen
```

To generate documentation from the source code:
```shell
doxygen Doxyfile
```
To view the generated documentation, open `html/index.html` in a web browser.


## Compiling
Use the `-ljson-c` and `-lsqlite3` flags when compiling with `gcc`:
```shell
gcc -o fdg json-c_sec.c main.c -ljson-c -lsqlite3
```

...or, if you want the compiler to show all warnings:
```shell
gcc -o fdg json-c_sec.c main.c -ljson-c -lsqlite3 -Wshadow -Wwrite-strings -Wextra -Wconversion -std=c11 -pedantic
```
If you get the error `ld: library not found for -ljsonc
clang: error: linker command failed with exit code 1`, first run `brew uninstall json-c` then `brew install json-c` again

## Version schedule
+ **v1.0.0**
   + Builds database of basic line items (i.e., those used in personal financial research) of all companies from SEC data
   + Calculations
      + Provides summary of any given company
         + 10- and 20-year average and median ROIC
         + Lists all unprofitable years
         + Indicates how many years and which years the database has data for given company
         + Shows lowest three years' debt-interest coverage
         + Shows price per seven-year average net income
      + Orders all publicly traded companies by average or median ROIC over any number of most recent years
         + This list also provides a summary of unprofitability, debt-interest coverage, and price

### Features to schedule
+ Offers pre-built portfolio/index/ETF aggregates
   + Same calculations as for individual companies
+ Allows users to create their own portfolio/index/ETF aggregates
+ Provides buy/sell target prices for stocks/ETFs based on price per average/median last seven years' Net Income


[json-c]: https://github.com/json-c/json-c
[json-c_homebrew]: https://formulae.brew.sh/formula/json-c
[sqlite]: https://www.sqlite.org/index.html
[doxygen]: https://www.doxygen.nl/
[EDGAR_APIs]: https://www.sec.gov/edgar/sec-api-documentation
