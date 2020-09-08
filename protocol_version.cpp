/*
 * SPDX-License-Identifier: MIT
 *
 * The MIT License (MIT)
 *
 * Copyright (c) <2020> Matthias Loy, Stephan Gatzka
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <cstring>
#include <iostream>

#include <boost/asio/streambuf.hpp>
#include <boost/endian/conversion.hpp>

#include "protocol_version.h"

namespace scramjet {
	protocol_version::protocol_version(boost::asio::streambuf& receive_buffer)
	{
		std::memcpy(&m_major, boost::asio::buffer_cast<const void*>(receive_buffer.data()), sizeof(m_major));
		receive_buffer.consume(sizeof(m_major));
		boost::endian::little_to_native_inplace(m_major);

		std::memcpy(&m_minor, boost::asio::buffer_cast<const void*>(receive_buffer.data()), sizeof(m_minor));
		receive_buffer.consume(sizeof(m_minor));
		boost::endian::little_to_native_inplace(m_minor);

		std::memcpy(&m_patch, boost::asio::buffer_cast<const void*>(receive_buffer.data()), sizeof(m_patch));
		receive_buffer.consume(sizeof(m_patch));
		boost::endian::little_to_native_inplace(m_patch);
	}

	void protocol_version::print() const
	{
		std::cout << "Protocol version: " << std::dec << m_major << "." << m_minor << "." << m_patch << std::endl;
	}
}
