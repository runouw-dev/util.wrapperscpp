#pragma once

#include <functional>
#include <memory>

namespace wrappers {
	template <class T>
	class lazy_ptr {
	private:
		std::unique_ptr<T> _instance;
		std::function<T()> _constructor;
		bool _init;

	public:
		lazy_ptr(const std::function<T()>& constructor) :
			_instance(nullptr),
			_constructor(constructor),
			_init(false) {}

		lazy_ptr(lazy_ptr<T>&) = delete;
		lazy_ptr(lazy_ptr<T>&&) = default;
		~lazy_ptr() = default;

		lazy_ptr<T>& operator=(lazy_ptr<T>&) = delete;
		lazy_ptr<T>& operator=(lazy_ptr<T>&&) = default;

		T * get();

		T& operator*();

		T * operator->();

		T * restore();

		bool isInitialized() const;
	};

	template<class T>
	bool lazy_ptr<T>::isInitialized() const {
		return _init;
	}

	template<class T>
	T * lazy_ptr<T>::get() {
		if (_init) {
			return _instance.get();
		} else {
			return restore();
		}
	}

	template<class T>
	T * lazy_ptr<T>::restore() {
		auto newPtr = std::make_unique<T> (_constructor());

		_instance.swap(newPtr);
		_init = true;
		
		return _instance.get();
	}

	template<class T>
	T& lazy_ptr<T>::operator*() {
		return *get();
	}

	template<class T>
	T * lazy_ptr<T>::operator->() {
		return get();
	}
}
