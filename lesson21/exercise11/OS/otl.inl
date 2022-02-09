/* Order template library */

//-----------------------------------------------------------------------------------------------

template<typename Container>
void order_upload(const Container& ord, string file_name, bool add)
{
	ofstream to(file_name, add ? ios_base::app : ios_base::ate);
	if (!to) { throw runtime_error("cant open " + file_name + " to write"); }

	for (const Order& p : ord) {
		to << "{ " << p.customer_info() << " : ";
		for (int i{ 0 }; i < p.check_size(); ++i)
			{ to << '[' << p[i] << ']'; }
		to << " }\n";
	}
}

//-----------------------------------------------------------------------------------------------

template<typename Container>
void order_download(Container& ord, string file_name)
{
	ifstream from(file_name);
	if (!from) { throw runtime_error("cant open " + file_name + " to read"); }

	copy(istream_iterator<Order>(from),
		 istream_iterator<Order>(),
		 back_inserter(ord));
}

//-----------------------------------------------------------------------------------------------

template<typename Iter, typename Compare>
void Sort(typename Iter b, typename Iter e, Compare comp)
{
	auto ee = e;
	--ee;
	for (auto checked = b; checked != e; ++checked) {
		auto* chosen = &*checked;
		for (auto verifiable = ee; verifiable != checked; --verifiable)
			if (!comp(*chosen, *verifiable))
				{ chosen = &*verifiable; }
		if (&*checked != chosen) {
			auto buf = *checked;
			*checked = *chosen;
			*chosen = buf;
		}
	}
}

//-----------------------------------------------------------------------------------------------

template<typename Container>
void sort_and_safe(Container& ords, string file)
{
	order_download(ords, file);
	for (const Order& p : ords)
		{ cout << p; }

	Sort(ords.begin(), ords.end(), [](const Order& left, const Order& right)
		{ return left.get_name() < right.get_name(); });
	order_upload(ords, "orders2.txt", false);
}

//-----------------------------------------------------------------------------------------------
