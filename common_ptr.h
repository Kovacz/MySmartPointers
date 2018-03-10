#ifndef COMMON_PTR_H
#define COMMON_PTR_H

namespace mypointer
{
	typedef size_t uint32;
	template<typename T>
	class common_ptr
	{
	public:
		typedef T* type_ptr;
		typedef T& type_ref;

		common_ptr() noexcept;
		explicit common_ptr(const type_ptr &p) noexcept;
		common_ptr(const common_ptr<T> &cp) noexcept;
		~common_ptr();

		type_ref operator*() const noexcept;
		type_ptr operator->() const noexcept;
		common_ptr &operator=(const common_ptr<T> &cp);

		uint32 get_count() const noexcept;
		void reset();
	private:
		type_ptr ptr;
		uint32 *counter;
	};

	template<typename T>
	common_ptr<T>::common_ptr() noexcept
		: ptr(nullptr),
		counter(nullptr)
	{
		std::cout << "common_ptr() \t\t" << this << " = " << ptr << std::endl;
	}

	template<typename T>
	common_ptr<T>::common_ptr(const type_ptr &p) noexcept
		: ptr(p),
		counter(new uint32(1))
	{
		std::cout << "common_ptr(pointer) \t" << this << " = " << ptr << std::endl;
	}

	template<typename T>
	common_ptr<T>::common_ptr(const common_ptr &cp) noexcept
		: common_ptr(cp.ptr)
	{
		counter = cp.counter;
		++*counter;
		std::cout << "common_ptr(copy) \t" << this << " = " << ptr << std::endl;
	}

	template<typename T>
	common_ptr<T>::~common_ptr()
	{
		std::cout << "~common_ptr() \t\t" << this << std::endl;
		if (*counter == 1) {
			std::cout << "destroyed \t\t" << this << " = " << ptr << std::endl;
			delete ptr;
			delete counter;
		} else if (*counter > 1) {
			ptr = nullptr;
			std::cout << "pointer \t\t" << this << " = nullptr" << std::endl;
			--*counter;
		}
	}

	template<typename T>
	typename common_ptr<T>::type_ref common_ptr<T>::operator*() const noexcept
	{
		return *ptr;
	}

	template<typename T>
	typename common_ptr<T>::type_ptr common_ptr<T>::operator->() const noexcept
	{
		return ptr;
	}

	template<typename T>
	common_ptr<T> &common_ptr<T>::operator=(const common_ptr<T> &cp)
	{
		if (this != &cp) {
			reset();
			ptr = cp.ptr;
			counter = cp.counter;
			++*counter;
		}
		std::cout << "::operator= \t\t" << this << " = " << ptr << std::endl;
		return *this;
	}

	template<typename T>
	uint32 common_ptr<T>::get_count() const noexcept
	{
		return *counter;
	}

	template<typename T>
	void common_ptr<T>::reset()
	{
		//this->~common_ptr();
		ptr = nullptr;
		counter = nullptr;
	}
}

#endif
