/* The copyright in this software is being made available under the BSD
 * Licence, included below.  This software may be subject to other third
 * party and contributor rights, including patent rights, and no such
 * rights are granted under this licence.
 *
 * Copyright (c) 2017-2018, ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of the ISO/IEC nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "ArithmeticCodec.h"
#include "PCCMisc.h"
#include "PCCTMC3Common.h"
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>

namespace pcc {

//============================================================================
// Opaque definitions (Internal detail)

struct PCCResidualsDecoder;

//============================================================================

class AttributeDecoder {
public:
  void buildPredictors(
    const PCCPointSet3 &pointCloud);

  // todo(df): return value is always 0 => should be void?
  int decodeHeader(
    const std::string &attributeName,
    PCCBitstream &bitstream);

  // todo(df): return value is always 0 =>  should be void?
  int decodeReflectances(
    PCCBitstream &bitstream,
    PCCPointSet3 &pointCloud);

  // todo(df): return value is always 0 => should be void?
  int decodeColors(
    PCCBitstream &bitstream,
    PCCPointSet3 &pointCloud);

protected:
  // todo(df): consider alternative encapsulation

  void decodeReflectancesIntegerLift(
    PCCResidualsDecoder &decoder,
    PCCPointSet3 &pointCloud);

  void decodeColorsIntegerLift(
    PCCResidualsDecoder &decoder,
    PCCPointSet3 &pointCloud);

  void decodeReflectancesRaht(
    PCCResidualsDecoder &decoder,
    PCCPointSet3 &pointCloud);

  void decodeColorsRaht(
    PCCResidualsDecoder &decoder,
    PCCPointSet3 &pointCloud);

private:
  std::vector<PCCPredictor> predictors;
  std::vector<int64_t> quantizationSteps;
  std::vector<size_t> dist2;
  size_t numberOfNearestNeighborsInPrediction;
  size_t levelOfDetailCount;
  uint32_t quantizationStepRaht;
  uint8_t depthRaht;
  uint8_t binaryLevelThresholdRaht;
  TransformType transformType;

};

//============================================================================

} /* namespace pcc */