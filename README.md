Search IMDb by Actor/Actress or by Movie

Datasets available at: https://datasets.imdbws.com/
Download name.basics.tsv, title.basics.tsv, title.principals.tsv and put them in a folder

build: 'make'
run: './a3 [dataset folder]'

When run the datasets will be compiled into search trees (this will take a while becuase of large datasets). 
Search results will be determined by efficiently cross comparing values between all trees.