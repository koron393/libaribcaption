/*
 * Copyright (C) 2021 magicxqq <xqq@xqq.im>. All rights reserved.
 *
 * This file is part of libaribcaption.
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "aribcaption/decoder.hpp"
#include "decoder/decoder_impl.hpp"

namespace aribcaption {

Decoder::Decoder(Context& context) : pimpl_(std::make_unique<internal::DecoderImpl>(context)) {}

Decoder::~Decoder() = default;

bool Decoder::Initialize(B24Type type, B24Profile profile, B24LanguageId language_id) {
    return pimpl_->Initialize(type, profile, language_id);
}

void Decoder::SetType(B24Type type) {
    pimpl_->SetType(type);
}

void Decoder::SetProfile(B24Profile profile) {
    pimpl_->SetProfile(profile);
}

void Decoder::SetLanguageId(B24LanguageId language_id) {
    pimpl_->SetLanguageId(language_id);
}

void Decoder::SetDefaultLanguage(uint32_t iso6392_language_code) {
    pimpl_->SetDefaultLanguage(iso6392_language_code);
}

uint32_t Decoder::QueryISO6392LanguageCode(B24LanguageId language_id) const {
    return pimpl_->QueryISO6392LanguageCode(language_id);
}

DecodeStatus Decoder::Decode(const uint8_t* pes_data, size_t length, int64_t pts, DecodeResult& out_result) {
    return pimpl_->Decode(pes_data, length, pts, out_result);
}

bool Decoder::Flush() {
    return pimpl_->Flush();
}

}  // namespace aribcaption
