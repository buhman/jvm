set -eux

make4ht $1 "pic-m,pic-equation,svg"

css="$(basename ${1%.tex}.css)"

mv "$(basename ${1%.tex}.html)" index.html
mv "${css}" index.css

echo 'img[alt="PIC"] { width: 100%; }' >> index.css
echo '.cmtt-10 { font-size: 0.9em; }' >> index.css
echo 'img[src="index3x.svg"] { height: 2.5em; }' >> index.css
echo 'object[class="graphics"] { width: 100% }' >> index.css

sed -i '/prefers-color-scheme/d' index.css
sed -i 's/1.5157em/1.3157em/g' index.css
sed -i 's/1.3195em/1.0195em/g' index.css

sed -i 's| </span>|</span> |g' index.html
sed -i "s/${css}/index.css/g" index.html
