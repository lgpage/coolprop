
cd ../../CoolProp

include_string = '-I.'

system('erase *_wrap.cpp')
system('call swig -octave -c++ -o CoolProp_wrap.cpp CoolProp.i')
main_files = glob('*.cpp');
files=[main_files];
o_files = ''
cpp_files = ''

for i=1:size(files)(1)
	file = files{i,1};
	o_file = strrep(file,'.cpp','.o');
	o_files = [o_files, ' ', o_file];
	cpp_files = [cpp_files, ' ',file];
	eval(['mkoctfile -v -c ', include_string,' -o ',o_file,' ',file])
end

eval(['mkoctfile -v ', include_string,' -o CoolProp.oct CoolProp_wrap.cpp',o_files])

% Clean up - remove the object files
for i=1:size(files)(1)
	file = files{i,1};
	o_file = strrep(file,'.cpp','.o');
	unlink(o_file);
	disp(['deleting the file ',o_file]);
end

unlink('CoolProp.exp')
unlink('CoolProp.lib')
unlink('CoolProp_wrap.o')
unlink('CoolProp_wrap.cpp')
