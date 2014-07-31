//create markdown table header
template<class S, class ... Types>
inline void table_header(S && stream, const char * format, const char  * first_name, Types ... rest_name)
{
	stream << "| " << first_name << " ";
	table_header(stream, format, rest_name...);
}

//table_header recursion base case
template <class S>
inline void table_header(S && stream, const char * format)
{
	stream << "|\n";

	for (char const* pos = format; *pos; ++pos)
		switch (*pos)
	{
		case 'l':
			stream << "|:--- ";
			break;
		case 'r':
			stream << "| ---:";
			break;
		case 'c':
			stream << "|:---:";
			break;
		default:
			break;
	}
	stream << "|\n";
}

//create markdown table row
template <class S, typename ... Types>
inline void table_row(S && stream, const char * first_content, Types  ... rest_content)
{
	stream << "| " << first_content << " ";
	table_row(stream, rest_content...);
}

//table_row recursion base case
template <class S>
inline void table_row(S && stream)
{
	stream << "|\n";
}

//create markdown heading
template <class S>
inline void heading(S && stream, unsigned char const level, const char * name)
{
	for (decltype(level) i = 0; i < level; ++i)
		stream << "#";
	stream << " " << name << "\n";
}

//create an html anchor. To be paired with an anchor link
template <class S>
inline void anchor(S && stream, const char * name)
{
	stream << "<a name = \"" << name << "\"></a>\n";
}

//create a markdown anchor link. To be paired with anchor
template <class S>
inline void anchor_link(S && stream, const char * content, const char * name)
{
	stream << "[" << content << "](#" << name << ")\n";
}

