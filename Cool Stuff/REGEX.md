# Translate a Markdown link to HTML using Regular Expressions

### Lets say we have the following file
```
[Google](https://www.google.com/)
[FMI](https://www.fmi.uni-sofia.bg/)
[My GitHub](https://github.com/metalfen4eto)
```
Now let us select only every Markdown link and rewrite it into HTML.
We will select using the following REGEX in find:
```regex
\[(.*?)]\((http.*?)\)
```
And if we replace it with:
```regex
<a href="$2">$1</a>
```
we get:
```r
<A href="https://www.google.com/">Google</a>
<A Href="https://www.fmi.uni-sofia.bg/">FMI</a>
<A href="https://github.com/metalfen4eto">my GitHub</a>
```

### How it works:
#### in the regular expression we search for this exact pattern:

*all of this is in group $0
- a opening square bracket literal ```\[```

- we group this in $1 ```(```
	- 0 or more ```*``` wildcard characters ```.``` 
	- non-greedily ```?``` (we want to stop at the first closing bracket)
- we close group $1 ```)```

- a closing bracket ```]```

- a opening bracket literal ```\(```

- we group this in $2 ```(```
	- the exact sequence of characters ```http```
	- 0 or more ```*``` wildcard characters ```.``` 
	- non-greedily ```?```
- we close group $2

- a closing bracket literal ```\)```