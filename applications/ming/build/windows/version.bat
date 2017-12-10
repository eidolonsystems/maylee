cd %~dp0../..
mkdir include
cd include
mkdir ming
cd %~dp0
printf "#define MING_VERSION """> %~dp0../../include/ming/version.hpp
git rev-list --count --first-parent HEAD | tr -d "\n\" >> %~dp0../../include/ming/version.hpp
printf """\n" >> %~dp0../../include/ming/version.hpp
